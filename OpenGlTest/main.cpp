#include <Windows.h>
#include <cstdio>
#include <math.h>
#include <gl/GL.h>
#include "OpenGlWindow.h"
#include "Vector3D.h"
#include "Bitmap.h"
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
PFNGLBUFFERDATAPROC    glBufferData;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

//Vertex attributes
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;


//Buffers
GLuint buffers;
GLuint texture;
GLuint VBO, VAO;

// Create checkerboard texture
#define textureHeight 1024
#define textureWidth 1024
static GLubyte checkImage[textureHeight][textureWidth][4];

//--------------------------------------------------------------
void GenerateTexture()
{
    for (int i = 0; i < textureHeight; i++)
    {
        for (int j = 0; j < textureWidth; j++)
        {
            double x = j / ((double)textureWidth - 1);
            double y = i / ((double)textureHeight - 1);
            x = (x - 0.5) * 2;
            y = (y - 0.5) * 2;

            double r = sqrt(x * x + y * y);
            if (r > 1)
            {
                checkImage[i][j][0] = (GLubyte)255;
                checkImage[i][j][1] = (GLubyte)0;
                checkImage[i][j][2] = (GLubyte)0;
                checkImage[i][j][3] = (GLubyte)255;
            }
            else
            {
                checkImage[i][j][0] = (GLubyte)((1-r) * 255);
                checkImage[i][j][1] = (GLubyte)((1-r) * 255);
                checkImage[i][j][2] = (GLubyte)((1-r) * 255);
                checkImage[i][j][3] = (GLubyte)255;
            }
        }
    }
}

//--------------------------------------------------------------
void Initialize()
{
    //Initialize GL matrices with identity matrix
    //glMatrixMode(GL_PROJECTION); // Scale of the underlying coordinate system
    //glLoadIdentity();
    //glFrustum(-1, 1, -1, 1, 4, 10);
    //GLenum error = glGetError();

    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glPushMatrix();

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    //glEnable(GL_TEXTURE_2D);
    ////Lighting
    //GLfloat light_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    //GLfloat mat_specular[] = { 1, 1, 1, 1 };
    //GLfloat mat_shininess[] = { 20.0 };
    //GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 }; //light straight from the front 
    //glShadeModel(GL_SMOOTH);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    //glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    //glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //Color that gets set when callid glClear()
    glClearColor(0.1f, 0, 0, 0);

    // Buffers
    glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
    glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
    glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");

    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");


    glGenVertexArrays(1, &VAO); // VAO holds our vertex data
    glGenBuffers(1, &VBO); //VBO is data one our graphics card

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(2);

    ////Texture   
    //Bitmap bitmap("SphereTexture.bmp");

    //glGenTextures(1, &texture);
    //glBindTexture(GL_TEXTURE_2D, texture);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.Width(), bitmap.Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.Data());
    //
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NONE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NONE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //glEnable(GL_TEXTURE_GEN_S);
    //glEnable(GL_TEXTURE_GEN_T);
    //glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    //glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

    //glMatrixMode(GL_PROJECTION);
}

//--------------------------------------------------------------
void RenderCube(float size = 0.35)
{  
    Cube cube(size);
    std::vector<Vertex> vertices = cube.GenerateMesh();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

//--------------------------------------------------------------
void RenderTorus(double r = 0.12, double c = 0.45, int rSeg = 50, int cSeg = 150)
{
    Torus torus(r, c, rSeg, cSeg);
    std::vector<Vertex> vertices = torus.GenerateMesh(); //is a little different because the triangle stripe is not per rotation
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size()); //10 is the size of a vertex with normal, color,...

}

//--------------------------------------------------------------
void RenderSphere(float r = 0.075, int latSeg = 150, int longSeg = 100)
{
    Sphere sphere(r, latSeg, longSeg);
    std::vector<Vertex> vertices = sphere.GenerateMesh();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());
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
    //window._shaderProgram = &shaderProgram;
    shaderProgram.Load("Shaders/shader.vert", "Shaders/shader.frag");

    Mat4 projection = Mat4::Perspective(1, 1, 0.5, 10); // Is the Camera lense
    //projection.Projection(1, 2, 0.5f, 10);
    Mat4 view; // Is the Camera position
    Mat4 model;
    window._viewMatrix = &view;
    Initialize();
    float angle = 0;

    //model.Rotate((3.142 * 2) / 4, 0, 0, 1);

    while (true)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Use();
        model = Mat4::Translate(0, 0, -3) * Mat4::Rotate(angle, 0, 1, 0);
        shaderProgram.SetMatrix("projectionMatrix", projection.Transpose());
        shaderProgram.SetMatrix("viewMatrix", view.Transpose());

        angle += 0.01;

        shaderProgram.SetMatrix("modelMatrix", model.Transpose());
        RenderTorus();
        //shaderProgram.SetMatrix("modelViewMatrix", model);
        RenderSphere(0.2);
        //model.Translate(0.4, 0, 0);
        //shaderProgram.SetMatrix("modelViewMatrix", model);
        //RenderCube();

        window.SwapBuffer();
        window.Update();
    }
    
    system("pause");
    return 0;
}

