#include <Windows.h>
#include <cstdio>
#include <math.h>
#include <gl/GL.h>
#include "OpenGlWindow.h"
#include "Vector3D.h"
#include "Bitmap.h"

//Defines that are not in GL 1.1
#define GL_ARRAY_BUFFER_ARB               0x8892
#define GL_ELEMENT_ARRAY_BUFFER_ARB       0x8893
#define GL_STATIC_DRAW_ARB                0x88E4   

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
GLuint texture;

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
    glMatrixMode(GL_PROJECTION); // Scale of the underlying coordinate system
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 4, 10);
    GLenum error = glGetError();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    //Lighting
    GLfloat light_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
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

    //Texture   
    Bitmap bitmap("SphereTexture.bmp");

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.Width(), bitmap.Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.Data());
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NONE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NONE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

    glMatrixMode(GL_PROJECTION);
}

//--------------------------------------------------------------
void RenderCube(float size = 0.15)
{  
    glBegin(GL_QUADS);
    //Back 
    {
        //Clockwise
        float a[] = { -size, -size, size }; //Upper left
        float b[] = { -size, size, size }; //Lower Left
        float c[] = { size, size, size }; //Lower Right
        float d[] = { size, -size, size }; //Upper Right
        //glColor3b(100, 100, 0);
        glNormal3fv(NormalVector(a, b, c).Data());
        glTexCoord2f(0, 0); glVertex3fv(a);
        glTexCoord2f(0, 1); glVertex3fv(b);
        glTexCoord2f(1, 1); glVertex3fv(c);
        glTexCoord2f(1, 0); glVertex3fv(d);
    }
    //Front
    {
        float a[] = { -size, -size, -size };
        float b[] = { size, -size, -size }; 
        float c[] = { size, size, -size };
        float d[] = { -size, size, -size };
        //glColor3b(100, 0, 0);
        glNormal3fv(NormalVector(a, b, c).Data());
        glTexCoord2f(0, 0); glVertex3fv(a);
        glTexCoord2f(0, 1); glVertex3fv(b);
        glTexCoord2f(1, 1); glVertex3fv(c);
        glTexCoord2f(1, 0); glVertex3fv(d);
    }
    //Bottom
    {
        float a[] = { size, -size, size };
        float b[] = { -size, -size, size };
        float c[] = { -size, -size, -size };
        float d[] = { size, -size, -size };
        //glColor3b(0, 0, 100);
        glNormal3fv(NormalVector(a, b, c).Data());
        glTexCoord2f(0, 0); glVertex3fv(a);
        glTexCoord2f(0, 1); glVertex3fv(b);
        glTexCoord2f(1, 1); glVertex3fv(c);
        glTexCoord2f(1, 0); glVertex3fv(d);
    }
    //Top
    {
        float a[] = { -size, size, size };
        float b[] = { size, size, size };
        float c[] = { size, size, -size };
        float d[] = { -size, size, -size };
        //glColor3b(0, 100, 0);
        glNormal3fv(NormalVector(a, b, c).Data());
        glTexCoord2f(0, 0); glVertex3fv(a);
        glTexCoord2f(0, 1); glVertex3fv(b);
        glTexCoord2f(1, 1); glVertex3fv(c);
        glTexCoord2f(1, 0); glVertex3fv(d);
    }
    //Left
    {
        float a[] = { -size, size, size };
        float b[] = { -size, -size, size };
        float c[] = { -size, -size, -size };
        float d[] = { -size, size, -size };
        //glColor3b(100, 100, 100);
        glNormal3fv(NormalVector(a, b, c).Data());
        glTexCoord2f(0, 0); glVertex3fv(a);
        glTexCoord2f(0, 1); glVertex3fv(b);
        glTexCoord2f(1, 1); glVertex3fv(c);
        glTexCoord2f(1, 0); glVertex3fv(d);
    }
    //Right
    {
        float a[] = { size, -size, size };
        float b[] = { size, size, size };
        float c[] = { size, size, -size };
        float d[] = { size, -size, -size };
        //glColor3b(0, 100, 100);
        glNormal3fv(NormalVector(a, b, c).Data());
        glTexCoord2f(0, 0); glVertex3fv(a);
        glTexCoord2f(0, 1); glVertex3fv(b);
        glTexCoord2f(1, 1); glVertex3fv(c);
        glTexCoord2f(1, 0); glVertex3fv(d);
    }
    glEnd();
}

//--------------------------------------------------------------
void RenderTorus(double r = 0.12, double c = 0.35, int rSeg = 150, int cSeg = 100)
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
                glNormal3d(u, v, w);
                glTexCoord2d(u * 0.5 + 0.5, v * 0.5 + 0.5);
                glVertex3d(2 * x, 2 * y, 2 * z);
            }
        }
        glEnd();
    }
}

//--------------------------------------------------------------
void RenderSphere(double r = 0.075, int latSeg = 150, int longSeg = 100)
{

    const double TAU = 2 * M_PI;

    for (int i = 0; i < latSeg; i++)
    {
        glBegin(GL_QUAD_STRIP);
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
                glNormal3d(u, v, w);
                glTexCoord2d(u * 0.5 + 0.5, v * 0.5 + 0.5);
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

    glTranslatef(-0.2f, 0, 0);
    RenderSphere();
    glTranslatef(+0.2f, 0, 0);
    RenderTorus();
    glTranslatef(+0.2f, 0, 0);
    RenderCube();
    glTranslatef(-0.2f, 0, 0);
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
    MoveCamera(0, 0, -6);
    while (true)
    {
        Render();
        window.SwapBuffer();
        window.Update();
    }
    
    system("pause");
    return 0;
}

