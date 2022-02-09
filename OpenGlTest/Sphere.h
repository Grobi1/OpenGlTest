#pragma once
#include "Model3D.h"
class Sphere : public Model3D
{
public:
    Sphere(float r = 0.075, int latSeg = 150, int longSeg = 100);
    virtual std::vector<Vertex> GenerateMesh();
private:
    float _r;
    float _latSeg;
    float _longSeg;
};

