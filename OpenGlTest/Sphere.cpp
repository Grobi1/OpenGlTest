#include "Sphere.h"

//--------------------------------------------------------------
Sphere::Sphere(float r, int latSeg, int longSeg)
{
    _r = r;
    _latSeg = latSeg;
    _longSeg = longSeg;
}

//--------------------------------------------------------------
std::vector<Vertex> Sphere::GenerateMesh()
{
    const double TAU = 2 * M_PI;
    std::vector<Vertex> vertices;

    for (int i = 0; i < _latSeg; i++)
    {
        for (int j = 0; j <= _longSeg; j++)
        {
            for (int k = 0; k <= 1; k++)
            {
                double rho = TAU / _latSeg * (i + k);
                double phi = TAU / _longSeg * j;
                double x = cos(phi) * sin(rho) * _r;
                double y = sin(phi) * sin(rho) * _r;
                double z = cos(rho) * _r;
                double u = cos(phi) * sin(rho);
                double v = sin(phi) * sin(rho);
                double w = cos(rho);
                Vertex vertex;
                vertex.position[0] = 2 * x;
                vertex.position[1] = 2 * y;
                vertex.position[2] = 2 * z;

                vertex.normal[0] = u;
                vertex.normal[1] = v;
                vertex.normal[2] = w;

                vertex.color[0] = 0.5;
                vertex.color[1] = 0.1;
                vertex.color[2] = 0.5;
                vertex.color[3] = 1;

                vertices.push_back(vertex);
            }
        }
    }
    return vertices;
}
