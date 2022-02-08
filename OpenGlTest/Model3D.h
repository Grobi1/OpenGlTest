#pragma once
#include <vector>

class Model3D
{
public:
    virtual std::vector<float> GenerateMesh() { return std::vector<float>(); }
};

