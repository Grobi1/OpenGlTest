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
    const float TAU = 2 * (float)M_PI;
    std::vector<Vertex> vertices;

    for (int i = 0; i < _latSeg; i++)
    {
        for (int j = 0; j <= _longSeg; j++)
        {
            for (int k = 0; k <= 1; k++)
            {
                float rho = TAU / _latSeg * (i + k);
                float phi = TAU / _longSeg * j;
                float x   = cosf(phi) * sinf(rho) * _r;
                float y   = sinf(phi) * sinf(rho) * _r;
                float z   = cosf(rho) * _r;
                float u   = cosf(phi) * sinf(rho);
                float v   = sinf(phi) * sinf(rho);
                float w   = cosf(rho);
                Vertex vertex;
                vertex.position[0] = 2 * x;
                vertex.position[1] = 2 * y;
                vertex.position[2] = 2 * z;

                vertex.normal[0] = u;
                vertex.normal[1] = v;
                vertex.normal[2] = w;

                vertex.color[0] = 0.5f;
                vertex.color[1] = 0.1f;
                vertex.color[2] = 0.5f;
                vertex.color[3] = 1;

                vertex.texture[0] = u * 0.5f + 0.5f;
                vertex.texture[1] = v * 0.5f + 0.5f;

                vertices.push_back(vertex);
            }
        }
    }
    return vertices;
}
