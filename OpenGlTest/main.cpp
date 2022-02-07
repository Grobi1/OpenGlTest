#include <Windows.h>
#include <cstdio>
#include <math.h>
#include <gl/GL.h>
#include "OpenGlWindow.h"
#include "Vector3D.h"
#include "Bitmap.h"
#include "gl/glext.h"
#include "ShaderProgram.h"

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
GLuint shaderProgram;

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
Vector3D NormalVector(float * a, float * b, float * c)
{
    Vector3D x = Vector3D(a) - Vector3D(b);
    Vector3D y = Vector3D(a) - Vector3D(c);
    Vector3D normalVector = Vector3D::CrossProduct(x, y);
    normalVector.Normalize();
    return normalVector;
}

//--------------------------------------------------------------
void Initialize()
{
    //Initialize GL matrices with identity matrix
    //glMatrixMode(GL_PROJECTION); // Scale of the underlying coordinate system
    //glLoadIdentity();
    ////glFrustum(-1, 1, -1, 1, 4, 10);
    //GLenum error = glGetError();

    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glPushMatrix();

    //glEnable(GL_BLEND);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_COLOR_MATERIAL);
    //glEnable(GL_TEXTURE_2D);
    //Lighting
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

    ShaderProgram shaderProgram;
    shaderProgram.Load("Shaders/shader.vert", "Shaders/shader.frag");
    shaderProgram.Use();


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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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
void RenderCube(float size = 0.15)
{  
    //glBegin(GL_QUADS);
    //Back 
    std::vector<float> vertices;
    {
        //Clockwise
        vertices.insert(vertices.end(), { -size, -size, size }); //Upper left
        vertices.insert(vertices.end(), { -size, size, size }); //Lower Left
        vertices.insert(vertices.end(), { size, size, size }); //Lower Right
        vertices.insert(vertices.end(), { size, -size, size }); //Upper Right
        //glColor3b(100, 100, 0);
        //glNormal3fv(NormalVector(a, b, c).Data());
        //glTexCoord2f(0, 0); glVertex3fv(a);
        //glTexCoord2f(0, 1); glVertex3fv(b);
        //glTexCoord2f(1, 1); glVertex3fv(c);
        //glTexCoord2f(1, 0); glVertex3fv(d);
    }
    //Front
    {
        vertices.insert(vertices.end(), { -size, -size, -size });
        vertices.insert(vertices.end(), { size, -size, -size });
        vertices.insert(vertices.end(), { size, size, -size });
        vertices.insert(vertices.end(), { -size, size, -size });
        //glColor3b(100, 0, 0);
        //glNormal3fv(NormalVector(a, b, c).Data());
        //glTexCoord2f(0, 0); glVertex3fv(a);
        //glTexCoord2f(0, 1); glVertex3fv(b);
        //glTexCoord2f(1, 1); glVertex3fv(c);
        //glTexCoord2f(1, 0); glVertex3fv(d);
    }
    //Bottom
    {
        vertices.insert(vertices.end(), { size, -size, size });
        vertices.insert(vertices.end(), { -size, -size, size });
        vertices.insert(vertices.end(), { -size, -size, -size });
        vertices.insert(vertices.end(), { size, -size, -size });
        //glColor3b(0, 0, 100);
        //glNormal3fv(NormalVector(a, b, c).Data());
        //glTexCoord2f(0, 0); glVertex3fv(a);
        //glTexCoord2f(0, 1); glVertex3fv(b);
        //glTexCoord2f(1, 1); glVertex3fv(c);
        //glTexCoord2f(1, 0); glVertex3fv(d);
    }
    //Top
    {
        vertices.insert(vertices.end(), { -size, size, size });
        vertices.insert(vertices.end(), { size, size, size });
        vertices.insert(vertices.end(), { size, size, -size });
        vertices.insert(vertices.end(), { -size, size, -size });
        //glColor3b(0, 100, 0);
        //glNormal3fv(NormalVector(a, b, c).Data());
        //glTexCoord2f(0, 0); glVertex3fv(a);
        //glTexCoord2f(0, 1); glVertex3fv(b);
        //glTexCoord2f(1, 1); glVertex3fv(c);
        //glTexCoord2f(1, 0); glVertex3fv(d);
    }
    //Left
    {
        vertices.insert(vertices.end(), { -size, size, size });
        vertices.insert(vertices.end(), { -size, -size, size });
        vertices.insert(vertices.end(), { -size, -size, -size });
        vertices.insert(vertices.end(), { -size, size, -size });
        //glColor3b(100, 100, 100);
        //glNormal3fv(NormalVector(a, b, c).Data());
        //glTexCoord2f(0, 0); glVertex3fv(a);
        //glTexCoord2f(0, 1); glVertex3fv(b);
        //glTexCoord2f(1, 1); glVertex3fv(c);
        //glTexCoord2f(1, 0); glVertex3fv(d);
    }
    //Right
    {
        vertices.insert(vertices.end(), { size, -size, size });
        vertices.insert(vertices.end(), { size, size, size });
        vertices.insert(vertices.end(), { size, size, -size });
        vertices.insert(vertices.end(), { size, -size, -size });
        //glColor3b(0, 100, 100);
        //glNormal3fv(NormalVector(a, b, c).Data());
        //glTexCoord2f(0, 0); glVertex3fv(a);
        //glTexCoord2f(0, 1); glVertex3fv(b);
        //glTexCoord2f(1, 1); glVertex3fv(c);
        //glTexCoord2f(1, 0); glVertex3fv(d);
    }
    //glEnd();
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glDrawArrays(GL_QUADS, 0, vertices.size());
}

//--------------------------------------------------------------
void RenderTorus(double r = 0.12, double c = 0.35, int rSeg = 150, int cSeg = 100)
{

    const double TAU = 2 * M_PI;
    std::vector<float> vertices;
    for (int i = 0; i < rSeg; i++)
    {
        //glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= cSeg; j++)
        {
            for (int k = 0; k <= 1; k++)
            {
                double rho = TAU / rSeg * (i + k);
                double phi = TAU / cSeg * j;
                double x = cos(phi) * (c + cos(rho) * r);
                double y = sin(phi) * (c + cos(rho) * r);
                double z = sin(rho) * r;
                double u = cos(rho) * cos(phi);
                double v = cos(rho) * sin(phi);
                double w = sin(rho);
                vertices.push_back(2 * x);
                vertices.push_back(2 * y);
                vertices.push_back(2 * z);
                //glNormal3d(u, v, w);
                //glTexCoord2d(u * 0.5 + 0.5, v * 0.5 + 0.5);
                //glVertex3d(2 * x, 2 * y, 2 * z);
            }
        }
        //glEnd();
    }
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glDrawArrays(GL_QUAD_STRIP, 0, vertices.size());
}

//--------------------------------------------------------------
void RenderSphere(double r = 0.075, int latSeg = 150, int longSeg = 100)
{
    std::vector<float> vertices;
    const double TAU = 2 * M_PI;

    for (int i = 0; i < latSeg; i++)
    {
        //glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= longSeg; j++)
        {
            for (int k = 0; k <= 1; k++)
            {
                double rho = TAU / latSeg * (i + k);
                double phi = TAU / longSeg * j;
                double x = cos(phi) * sin(rho) * r;
                double y = sin(phi) * sin(rho) * r;
                double z = cos(rho) * r;
                double u = cos(phi) * sin(rho);
                double v = sin(phi) * sin(rho);
                double w = cos(rho);
                vertices.push_back(2 * x);
                vertices.push_back(2 * y);
                vertices.push_back(2 * z);
                //glNormal3d(u, v, w);
                //glTexCoord2d(u * 0.5 + 0.5, v * 0.5 + 0.5);
               // glVertex3d(2 * x, 2 * y, 2 * z);
            }
        }
        //glEnd();
    }
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glDrawArrays(GL_QUAD_STRIP, 0, vertices.size());
}

//--------------------------------------------------------------
void Render()
{
    //glMatrixMode(GL_MODELVIEW);
    //glPopMatrix();

    //Save default matrix again
    //glPushMatrix(); //<- why

    //glTranslatef(_windowWidth / 2.f, _windowHeight / 2.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glTranslatef(-0.2f, 0, 0);
    RenderSphere();
    //glTranslatef(+0.2f, 0, 0);
    RenderTorus();
    //glTranslatef(+0.2f, 0, 0);
    RenderCube();
    //glTranslatef(-0.2f, 0, 0);
}

void MoveCamera(float x, float y, float z)
{
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    //glLoadIdentity();
    glTranslatef(x, y, z);
    glPushMatrix();
}

void RotateCamera(float angle, float x, float y, float z)
{
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    //glLoadIdentity(); // this resets our matrix
    glRotatef(angle, x, y, z);
    glPushMatrix();
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
    Initialize();



    //MoveCamera(0, 0, -6);
    while (true)
    {
        Render();
        window.SwapBuffer();
        window.Update();
    }
    
    system("pause");
    return 0;
}

