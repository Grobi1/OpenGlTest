#include <Windows.h>
#include <cstdio>
#include <math.h>
#include <gl/GL.h>
#include "OpenGlWindow.h"
#include "Vector3D.h"

//Defines that are not in GL 1.1
#define GL_ARRAY_BUFFER_ARB               0x8892
#define GL_ELEMENT_ARRAY_BUFFER_ARB       0x8893
#define GL_STATIC_DRAW_ARB                0x88E4   

//HDC drawingContext;

//typedef ptrdiff_t GLsizeiptr;
//typedef void (WINAPI * PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
//typedef void (WINAPI * PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint * buffers);
//typedef void (WINAPI * PFNGLGENBUFFERSPROC) (GLsizei n, GLuint * buffers);
//typedef void (WINAPI * PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage);
//
//PFNGLBINDBUFFERPROC    glBindBuffer;
//PFNGLDELETEBUFFERSPROC glDeleteBuffers;
//PFNGLGENBUFFERSPROC    glGenBuffers;
//PFNGLBUFFERDATAPROC    glBufferData;

//Buffers
GLuint buffers;

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
    glMatrixMode(GL_PROJECTION); // Scale of the underlying coordinate system
    glLoadIdentity();

    //glOrtho(-1, 1, 1, -1, 1, -1);
    glFrustum(-1, 1, 1, -1, 1, -1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);


    //Lighting
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat mat_specular[] = { 1, 1, 1, 1 };
    GLfloat mat_shininess[] = { 20.0 };
    GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 }; //light straight from the front 
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //Color that gets set when callid glClear()
    glClearColor(0, 0, 0, 0);


    //Get the extension function from opengl, these are not supported by everything and are therefore not exported
    //glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
    //glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
    //glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
    //glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");

    //glGenBuffers(1, &buffers); //Why 1 and not GL_ARRAY_BUFFER like in the book
    //glBufferData(GL_ARRAY_BUFFER_ARB, sizeof(vertices),
    //    vertices, GL_STATIC_DRAW_ARB);

}

//--------------------------------------------------------------
void RenderCube()
{
    glBegin(GL_QUADS);
    //Front 
    {
        //Clockwise
        float a[] = { -0.25, -0.25, 0.25 }; //Upper left
        float b[] = { -0.25, 0.25, 0.25 }; //Lower Left
        float c[] = { 0.25, 0.25, 0.25 }; //Lower Right
        float d[] = { 0.25, -0.25, 0.25 }; //Upper Right
        glColor3b(100, 100, 0);
        glNormal3fv(NormalVector(a, b, c).Data());
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
        glVertex3fv(d);
    }
    //Back
    {
        float a[] = { -0.25, -0.25, -0.25 };
        float b[] = { 0.25, -0.25, -0.25 }; 
        float c[] = { 0.25, 0.25, -0.25 };
        float d[] = { -0.25, 0.25, -0.25 };
        glColor3b(100, 0, 0);
        glNormal3fv(NormalVector(a, b, c).Data());
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
        glVertex3fv(d);
    }
    //Bottom
    {
        float a[] = { 0.25, -0.25, 0.25 };
        float b[] = { -0.25, -0.25, 0.25 };
        float c[] = { -0.25, -0.25, -0.25 };
        float d[] = { 0.25, -0.25, -0.25 };
        glColor3b(0, 0, 100);
        glNormal3fv(NormalVector(a, b, c).Data());
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
        glVertex3fv(d);
    }
    //Top
    {
        float a[] = { -0.25, 0.25, 0.25 };
        float b[] = { 0.25, 0.25, 0.25 };
        float c[] = { 0.25, 0.25, -0.25 };
        float d[] = { -0.25, 0.25, -0.25 };
        glColor3b(0, 100, 0);
        glNormal3fv(NormalVector(a, b, c).Data());
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
        glVertex3fv(d);
    }
    //Left
    {
        float a[] = { -0.25, 0.25, 0.25 };
        float b[] = { -0.25, -0.25, 0.25 };
        float c[] = { -0.25, -0.25, -0.25 };
        float d[] = { -0.25, 0.25, -0.25 };
        glColor3b(100, 100, 100);
        glNormal3fv(NormalVector(a, b, c).Data());
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
        glVertex3fv(d);
    }
    //Right
    {
        float a[] = { 0.25, -0.25, 0.25 };
        float b[] = { 0.25, 0.25, 0.25 };
        float c[] = { 0.25, 0.25, -0.25 };
        float d[] = { 0.25, -0.25, -0.25 };
        glColor3b(0, 100, 100);
        glNormal3fv(NormalVector(a, b, c).Data());
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
        glVertex3fv(d);
    }
    glEnd();
}

//--------------------------------------------------------------
void RenderTorus(double r = 0.08, double c = 0.35, int rSeg = 50, int cSeg = 100)
{

    const double TAU = 2 * M_PI;

    for (int i = 0; i < rSeg; i++)
    {
        glBegin(GL_QUAD_STRIP);
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
                glColor3b(i, j, 50);
                glNormal3f(-u, -v, -w);
                glVertex3d(2 * x, 2 * y, 2 * z);
            }
        }
        glEnd();
    }
}

//--------------------------------------------------------------
void Render()
{
    glMatrixMode(GL_MODELVIEW);
    //glPopMatrix();

    //Save default matrix again
    //glPushMatrix(); //<- why

    //glTranslatef(_windowWidth / 2.f, _windowHeight / 2.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    RenderCube();
    RenderTorus();
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
    while (true)
    {
        RotateCamera(1, 1, 1, 1);
        Render();
        window.SwapBuffer();
        window.Update();
    }
    
    system("pause");
    return 0;
}

