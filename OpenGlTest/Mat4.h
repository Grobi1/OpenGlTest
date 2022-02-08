#pragma once
class Mat4
{
public:
    Mat4();
    float * Data() { return &_data[0][0]; };
    Mat4 Reset();
    Mat4 Projection(float aspect, float fov, float near, float far);
    Mat4 Rotate(float angle, float x, float y, float z);
    Mat4 Translate(float x, float y, float z);
    Mat4 Multiply(Mat4 mat);
    Mat4 Scale(float x, float y, float z);
private:
    float _data[4][4];
};

