#include <Windows.h>
#include <cstdio>
#include <math.h>
#include "OpenGlWindow.h"
#include "Vector3D.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Mat4.h"
#include "Shapes.h"
#include "Vertex.h"

//--------------------------------------------------------------
//int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
//{
//    Initialize();
//}

//--------------------------------------------------------------
int main()
{
    OpenGlWindow window;

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0, 0, 0);

    ShaderProgram shaderProgram = ShaderProgram();
    shaderProgram.Load("Shaders/shader.vert", "Shaders/shader.frag");

    Mat4 projection = Mat4::Perspective(1, 1, 0.5, 10); // Is the Camera lense
    //projection.Projection(1, 2, 0.5f, 10);
    Mat4 view; // Is the Camera position
    Mat4 model;
    window._viewMatrix = &view;
    float angle = 0;


    Cube cube(0.15f);
    Torus torus;
    Sphere sphere(0.2f);

    Texture textureTest("TestImage.bmp");
    Texture sphereTexture("SphereTexture.bmp");
    sphereTexture.Bind();

    while (true)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Use();
        shaderProgram.SetMatrix("projectionMatrix", projection.Transpose());
        shaderProgram.SetMatrix("viewMatrix", view.Transpose());

        angle += 0.01f;
        
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

