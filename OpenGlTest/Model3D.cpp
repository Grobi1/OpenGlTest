#include <Windows.h>
#include "Model3D.h"
#include "OpenGl.h"



//--------------------------------------------------------------
Model3D::Model3D()
{
    _meshSize = 0;

    GL_CALL(glGenVertexArrays(1, (GLuint*)&_vao));
    GL_CALL(glGenBuffers(1, (GLuint*)&_vbo));

    GL_CALL(glBindVertexArray(_vao));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, _vbo));

    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color)));
    GL_CALL(glEnableVertexAttribArray(2));
    GL_CALL(glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture)));
    GL_CALL(glEnableVertexAttribArray(3));
}

//--------------------------------------------------------------
Model3D::~Model3D()
{
    GL_CALL(glDeleteVertexArrays(1, (GLuint*)&_vao));
    GL_CALL(glDeleteBuffers(1, (GLuint*)&_vbo));
}

//--------------------------------------------------------------
void Model3D::Render()
{
    GL_CALL(glBindVertexArray(_vao));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, _vbo));
    if (_meshSize == 0)
    {
         std::vector<Vertex> vertices = GenerateMesh();
        _meshSize = vertices.size();
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW));
    }
    
    GL_CALL(glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)_meshSize));

    //We are finished with this VAO and VBO so unbind so that something else does not write to it
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CALL(glBindVertexArray(0));
}
