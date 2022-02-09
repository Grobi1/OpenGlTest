#pragma once
#include "Model3D.h"

class Cube : Model3D
{
public:
    Cube(float size = 0.2);
    virtual std::vector<Vertex> GenerateMesh();
private:
    float _size;
};
