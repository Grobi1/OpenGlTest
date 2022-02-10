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
    const double TAU = 2 * M_PI;

    for (int i = 0; i < _rSeg; i++)
    {
        //glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= _cSeg; j++)
        {
            for (int k = 0; k <= 1; k++)
            {
                double rho = TAU / _rSeg * (i + k);
                double phi = TAU / _cSeg * j;
                double x = cos(phi) * (_c + cos(rho) * _r);
                double y = sin(phi) * (_c + cos(rho) * _r);
                double z = sin(rho) * _r;
                double u = cos(rho) * cos(phi);
                double v = cos(rho) * sin(phi);
                double w = sin(rho);

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

                vertex.texture[0] = u * 0.5 + 0.5;
                vertex.texture[1] = v * 0.5 + 0.5;

                vertices.push_back(vertex);
            }
        }
    }
    return vertices;
}
