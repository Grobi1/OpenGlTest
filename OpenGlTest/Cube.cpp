#include "Cube.h"
#include "Vector3D.h"

//--------------------------------------------------------------
Cube::Cube(float size)
{
    _size = size;
}

//--------------------------------------------------------------
std::vector<Vertex> Cube::GenerateMesh()
{
    std::vector<Vertex> vertices;
    float r = 0.5f;
    float g = 0.1f;
    float b = 0.5f;
    float a = 1;

    float corners[8][3] =
    {
        { -_size, -_size,  _size },
        {  _size, -_size,  _size },
        {  _size,  _size,  _size },
        { -_size,  _size,  _size },
        { -_size, -_size, -_size },
        {  _size, -_size, -_size }, 
        {  _size,  _size, -_size }, 
        { -_size,  _size, -_size } 
    };

    int indices[12][3]
    {
        {0, 1, 2}, //Front
        {2, 3, 0}, //Front
        {2, 1, 5}, //Left
        {2, 5, 6}, //Left
        {6, 5, 4}, //Back
        {6, 4, 7}, //Back
        {7, 4, 0}, //Right
        {7, 0, 3}, //Right
        {2, 3, 7}, //Bottom
        {6, 2, 7}, //Bottom
        {4, 0, 5}, //Top
        {1, 5, 0}  //Top
    };


    float textureCoords[8][2] =
    {
        { 0.f, 0.f, },
        { 1.f, 0.f, },
        { 1.f, 1.f, },
        { 0.f, 1.f, },
        { 0.f, 0.f, },
        { 1.f, 0.f, },
        { 1.f, 1.f, },
        { 0.f, 1.f, }
    };

    for (int triangleIndex = 0; triangleIndex < 12; triangleIndex++)
    {
        int cornerA = indices[triangleIndex][0];
        int cornerB = indices[triangleIndex][1];
        int cornerC = indices[triangleIndex][2];

        float* cornerAv = corners[cornerA];
        float* cornerBv = corners[cornerB];
        float* cornerCv = corners[cornerC];

        Vector3D normal = Vector3D::Normal(cornerAv, cornerBv, cornerCv);
        Vertex vertex;
        vertex.position[0] = cornerAv[0];
        vertex.position[1] = cornerAv[1];
        vertex.position[2] = cornerAv[2];
        vertex.normal[0] = normal.X();
        vertex.normal[1] = normal.Y();
        vertex.normal[2] = normal.Z();
        vertex.color[0] = 1;
        vertex.color[1] = 1;
        vertex.color[2] = 1;
        vertex.color[3] = 1;
        vertex.texture[0] = textureCoords[cornerA][0];
        vertex.texture[1] = textureCoords[cornerA][1];
        vertices.push_back(vertex);

        vertex.position[0] = cornerBv[0];
        vertex.position[1] = cornerBv[1];
        vertex.position[2] = cornerBv[2];
        vertex.texture[0] = textureCoords[cornerB][0];
        vertex.texture[1] = textureCoords[cornerB][1];
        vertices.push_back(vertex);

        vertex.position[0] = cornerCv[0];
        vertex.position[1] = cornerCv[1];
        vertex.position[2] = cornerCv[2];

        vertex.texture[0] = textureCoords[cornerC][0];
        vertex.texture[1] = textureCoords[cornerC][1];
        vertices.push_back(vertex);
    }
    return vertices;
}

