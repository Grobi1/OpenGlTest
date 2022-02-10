#include <Windows.h>
#include <cstdio>
#include <math.h>
#include <gl/GL.h>
#include "OpenGlWindow.h"
#include "Vector3D.h"
#include "Texture.h"
#include "gl/glext.h"
#include "ShaderProgram.h"
#include "Mat4.h"
#include "Cube.h"
#include "Sphere.h"
#include "Torus.h"
#include "Vertex.h"

// Buffers
PFNGLBINDBUFFERPROC    glBindBuffer;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLGENBUFFERSPROC    glGenBuffers;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

//Vertex attributes
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

//Buffers
GLuint VBO, VAO;

//--------------------------------------------------------------
void Initialize()
{

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0, 0, 0);

    // Buffers
    glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
    glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");

    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); 

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
    glEnableVertexAttribArray(3);
}

//--------------------------------------------------------------
//int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
//{
//    Initialize();
//}

//--------------------------------------------------------------
int main()
{
    OpenGlWindow window;
    ShaderProgram shaderProgram = ShaderProgram();
    shaderProgram.Load("Shaders/shader.vert", "Shaders/shader.frag");

    Mat4 projection = Mat4::Perspective(1, 1, 0.5, 10); // Is the Camera lense
    //projection.Projection(1, 2, 0.5f, 10);
    Mat4 view; // Is the Camera position
    Mat4 model;
    window._viewMatrix = &view;
    Initialize();
    float angle = 0;


    Cube cube(0.15);
    Torus torus;
    Sphere sphere(0.2);

    Texture textureTest("TestImage.bmp");
    Texture sphereTexture("SphereTexture.bmp");
    sphereTexture.Bind();

    while (true)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Use();
        shaderProgram.SetMatrix("projectionMatrix", projection.Transpose());
        shaderProgram.SetMatrix("viewMatrix", view.Transpose());

        angle += 0.01;
        
        Mat4 rotation = Mat4::Rotate(angle, 1, 0, 0);

        //model = Mat4::Translate(0, 0, -3) * rotation * Mat4::Translate(-0.2, 0, 0);
        //shaderProgram.SetMatrix("modelMatrix", model.Transpose());
        //cube.Render();

        model = Mat4::Translate(0, 0, -3) * rotation;
        shaderProgram.SetMatrix("modelMatrix", model.Transpose());
        torus.Render();

        model = Mat4::Translate(0, 0, -3) * rotation;// *Mat4::Translate(0.2, 0, 0);
        shaderProgram.SetMatrix("modelMatrix", model.Transpose());
        sphere.Render();


        shaderProgram.SetMatrix("normalMatrix", rotation.Transpose());

        window.SwapBuffer();
        window.Update();
    }
    
    system("pause");
    return 0;
}

