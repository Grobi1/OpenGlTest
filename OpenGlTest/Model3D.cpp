#include <Windows.h>
#include "Model3D.h"
#include "OpenGl.h"



//--------------------------------------------------------------
Model3D::Model3D()
{
    _meshSize = 0;

    glGenVertexArrays(1, (GLuint*)&_vao);
    glGenBuffers(1, (GLuint*)&_vbo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

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
Model3D::~Model3D()
{
    glDeleteVertexArrays(1, (GLuint*)&_vao);
    glDeleteBuffers(1, (GLuint*)&_vbo);
}

//--------------------------------------------------------------
void Model3D::Render()
{
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    if (_meshSize == 0)
    {
         std::vector<Vertex> vertices = GenerateMesh();
        _meshSize = vertices.size();
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    }
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)_meshSize);

    //We are finished with this VAO and VBO so unbind so that something else does not write to it
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
