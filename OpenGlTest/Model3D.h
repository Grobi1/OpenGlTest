#pragma once
#include <vector>
#include "Vertex.h"

class Model3D
{
public:
    virtual std::vector<Vertex> GenerateMesh() { return std::vector<Vertex>(); }
};

