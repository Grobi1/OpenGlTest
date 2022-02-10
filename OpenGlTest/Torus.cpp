#include "Torus.h"

//--------------------------------------------------------------
Torus::Torus(float r, float c, int rSeg, int cSeg)
{
    _r = r;
    _c = c;
    _rSeg = rSeg;
    _cSeg = cSeg;
}

//--------------------------------------------------------------
std::vector<Vertex> Torus::GenerateMesh()
{
    std::vector<Vertex> vertices;
    const float TAU = 2 * (float)M_PI;

    for (int i = 0; i < _rSeg; i++)
    {
        //glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= _cSeg; j++)
        {
            for (int k = 0; k <= 1; k++)
            {
                float rho = TAU / _rSeg * (i + k);
                float phi = TAU / _cSeg * j;
                float x = cosf(phi) * (_c + cosf(rho) * _r);
                float y = sinf(phi) * (_c + cosf(rho) * _r);
                float z = sinf(rho) * _r;
                float u = cosf(rho) * cosf(phi);
                float v = cosf(rho) * sinf(phi);
                float w = sinf(rho);

                Vertex vertex;
                vertex.position[0] = 2 * x;
                vertex.position[1] = 2 * y;
                vertex.position[2] = 2 * z;

                vertex.normal[0] = u;
                vertex.normal[1] = v;
                vertex.normal[2] = w;

                vertex.color[0] = 1;
                vertex.color[1] = 1;
                vertex.color[2] = 1;
                vertex.color[3] = 1;

                vertex.texture[0] = u * 0.5f + 0.5f;
                vertex.texture[1] = v * 0.5f + 0.5f;

                vertices.push_back(vertex);
            }
        }
    }
    return vertices;
}
