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
std::vector<float> Torus::GenerateMesh()
{
    std::vector<float> vertices;
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

                vertices.push_back(2 * x);
                vertices.push_back(2 * y);
                vertices.push_back(2 * z);

                vertices.push_back(0.1);
                vertices.push_back(0.5);
                vertices.push_back(0.1);
                vertices.push_back(1);

                vertices.push_back(u);
                vertices.push_back(v);
                vertices.push_back(w);
                //glTexCoord2d(u * 0.5 + 0.5, v * 0.5 + 0.5);
            }
        }
    }
    return vertices;
}
