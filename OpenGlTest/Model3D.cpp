#include <Windows.h>
#include "Model3D.h"
#include <gl/GL.h>
#include "gl/glext.h"

PFNGLBUFFERDATAPROC    glBufferData;

//--------------------------------------------------------------
Model3D::Model3D()
{
    // Probably better to wrap these all in one file/class?
    glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
}

//--------------------------------------------------------------
void Model3D::Render()
{
    //VBO stuff als in this class?
    std::vector<Vertex> vertices = GenerateMesh(); //We could also cache this mesh
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());
}
