#pragma once
class Mat4
{
public:
    Mat4();
    float * Data() { return *_data; };
    const float * Data() const { return *_data; };
    Mat4 Reset();
    Mat4 Transpose() const;
    static Mat4 Identity();
    static Mat4 Perspective(float aspect, float fov, float near, float far);
    static Mat4 Frustum(float left, float right, float bottom, float top, float near,  float far);
    static Mat4 Ortho(float left, float right, float bottom, float top, float near, float far);
    static Mat4 Rotate(float angle, float x, float y, float z);
    static Mat4 RotateX(float angle);
    static Mat4 RotateY(float angle);
    static Mat4 RotateZ(float angle);
    static Mat4 Translate(float x, float y, float z);
    static Mat4 Scale(float x, float y, float z);
private:
    float _data[4][4];
};

Mat4 operator * (const Mat4 &  a, const Mat4 & b);

