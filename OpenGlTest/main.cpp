#include <Windows.h>
#include <cstdio>
#include <math.h>
#include "OpenGl.h"
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
    OpenGl::Initialize();
    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glEnable(GL_DEPTH_TEST));
    GL_CALL(glClearColor(0.1f, 0, 0, 0));

    ShaderProgram shaderProgram = ShaderProgram("Shaders/shader.vert", "Shaders/shader.frag");

    Mat4 projection = Mat4::Perspective(1, 1, 0.5, 10); // Is the Camera lense
    //projection.Projection(1, 2, 0.5f, 10);
    Mat4 view; // Is the Camera position
    Mat4 model;
    window._viewMatrix = &view;
    float angle = 0;

    Cube cube(0.15f);
    Torus torus(0.09f, 0.35f);
    Torus torus2(0.12f, 0.6f);
    Sphere sphere(0.2f);

    Texture textureTest("TestImage.bmp");
    Texture sphereTexture("SphereTexture.bmp");
    sphereTexture.Bind();

    while (true)
    {
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        shaderProgram.Bind();
        shaderProgram.SetUniformMat4("projectionMatrix", projection.Transpose());
        shaderProgram.SetUniformMat4("viewMatrix", view.Transpose());

        angle += 0.01f;
        
        Mat4 rotation = Mat4::Rotate(angle, 1, 0, 0);

        //model = Mat4::Translate(0, 0, -3) * rotation * Mat4::Translate(-0.2, 0, 0);
        //shaderProgram.SetMatrix("modelMatrix", model.Transpose());
        //cube.Render();

        model = Mat4::Translate(0, 0, -3) * rotation;
        shaderProgram.SetUniformMat4("normalMatrix", rotation.Transpose());
        
        shaderProgram.SetUniformMat4("modelMatrix", model.Transpose());
        torus.Render();

        model = Mat4::Translate(0, 0, -3) * rotation;// *Mat4::Translate(0.2, 0, 0);
        shaderProgram.SetUniformMat4("modelMatrix", model.Transpose());
        sphere.Render();


        rotation = Mat4::Rotate(angle, 0, 1, 0);
        model = Mat4::Translate(0, 0, -3) * rotation;
        shaderProgram.SetUniformMat4("normalMatrix", rotation.Transpose());
        shaderProgram.SetUniformMat4("modelMatrix", model.Transpose());
        torus2.Render();




        window.SwapBuffer();
        window.Update();
    }
    
    system("pause");
    return 0;
}

