#pragma once
#include "Model3D.h"

class Torus : Model3D
{
public:
    Torus(float r = 0.12, float c = 0.45, int rSeg = 50, int cSeg = 150);
    virtual std::vector<Vertex> GenerateMesh();
private:
    float _r;
    float _c;
    float _rSeg;
    float _cSeg;
};

