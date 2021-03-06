#pragma once
#include <vector>
#include "Vertex.h"

class Model3D
{
public:
    Model3D();
    ~Model3D();
    virtual void Render();
    virtual std::vector<Vertex> GenerateMesh() { return std::vector<Vertex>(); }
private:
    size_t _meshSize;
    int _vao;
    int _vbo;
};

