#include "Mat4.h"
#include <math.h>

//--------------------------------------------------------------
Mat4::Mat4()
{
    Reset();
}
//--------------------------------------------------------------
Mat4 Mat4::Reset()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            _data[i][j] = 0;
    for (int i = 0; i < 4; i++)
        _data[i][i] = 1;
    return *this;
}

//--------------------------------------------------------------
Mat4 Mat4::Identity()
{
    return Mat4();
}

//--------------------------------------------------------------
Mat4 Mat4::Transpose() const
{
    Mat4 result;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result._data[i][j] = _data[j][i];

    return result;
}


//--------------------------------------------------------------
Mat4 Mat4::Perspective(float aspect, float fov, float near, float far)
{
    Mat4 mat;
    mat._data[0][0] = 1 / (aspect * tanf(fov / 2));
    mat._data[1][1] = 1 / (tanf(fov / 2));
    mat._data[2][2] = ((far + near) / (near - far));
    mat._data[2][3] = ((2 * far * near) / (near - far));
    mat._data[3][2] = -1;
    return mat;
}


//--------------------------------------------------------------
Mat4 Mat4::Frustum(float left, float right, float bottom, float top, float near, float far)
{
    Mat4 mat;
    mat._data[0][0] = 2 * near / (right - left);
    mat._data[0][2] = (right + left) / (right - left);
    mat._data[1][1] = 2 * near / (top - bottom);
    mat._data[1][2] = (top + bottom) / (top - bottom);
    mat._data[2][2] = -(far + near) / (far - near);
    mat._data[2][3] = -(2 * far * near) / (far - near);
    mat._data[3][2] = -1;
    return mat;
}

//--------------------------------------------------------------
Mat4 Mat4::Ortho(float left, float right, float bottom, float top, float near, float far)
{
    Mat4 mat;
    mat._data[0][0] = 2 / (right - left);
    mat._data[0][3] = -((right + left) / (right - left));
    mat._data[1][1] = 2  / (top - bottom);
    mat._data[1][3] = -((top + bottom) / (top - bottom));
    mat._data[2][2] = -2 / (far - near);
    mat._data[2][3] = -((far + near) / (far - near));
    mat._data[3][3] = 1;
    return mat;
}

//--------------------------------------------------------------
Mat4 Mat4::Rotate(float angle, float x, float y, float z)
{
    //https://www.cprogramming.com/tutorial/3d/rotation.html and https://learnopengl.com/Getting-started/Transformations
    //tX2 + c         tXY - sZ        tXZ + sY        0              
    //tXY+sZ          tY2 + c         tYZ - sX        0               
    //tXZ - sY        tYZ + sX        tZ2 + c         0

    Mat4 matRot;
    float t = 1 - cosf(angle);
    float s = sinf(angle);
    float c = cosf(angle);
    //tX2 + c         tXY - sZ        tXZ + sY        0 
    matRot._data[0][0] = t * x * x + c;
    matRot._data[1][0] = t * x * y - s * z;
    matRot._data[2][0] = t * x * z + s * y;

    //tXY+sZ          tY2 + c         tYZ - sX        0 
    matRot._data[0][1] = t * x * y + s * z;
    matRot._data[1][1] = t * y * y + c;
    matRot._data[2][1] = t * y * z - s * x;

    //tXZ - sY        tYZ + sX        tZ2 + c         0
    matRot._data[0][2] = t * x * z - s * y;
    matRot._data[1][2] = t * y * z + s * x;
    matRot._data[2][2] = t * z * z + c;
    return matRot;
}

//--------------------------------------------------------------
Mat4 Mat4::RotateX(float angle)
{
    Mat4 matX;
    matX._data[1][1] = (cosf(angle));
    matX._data[2][1] = (sinf(angle));                  
    matX._data[1][2] = (-sinf(angle));
    matX._data[2][2] = (cosf(angle));
    return matX;
}

//--------------------------------------------------------------
Mat4 Mat4::RotateY(float angle)
{
    Mat4 matY;
    matY._data[0][0] = (cosf(angle));
    matY._data[2][0] = (sinf(angle));
    matY._data[0][2] = (-sinf(angle));
    matY._data[2][2] = (cosf(angle));
    return matY;
}

//--------------------------------------------------------------
Mat4 Mat4::RotateZ(float angle)
{
    Mat4 matZ;
    matZ._data[0][0] = (cosf(angle));
    matZ._data[1][0] = (sinf(angle));
    matZ._data[0][1] = (-sinf(angle));
    matZ._data[1][1] = (cosf(angle));
    return matZ;
}

//--------------------------------------------------------------
Mat4 Mat4::Translate(float x, float y, float z)
{
    Mat4 trans;
    trans._data[0][3] = x;
    trans._data[1][3] = y;
    trans._data[2][3] = z;
    return trans;
}

//--------------------------------------------------------------
Mat4 Mat4::Scale(float x, float y, float z)
{
    Mat4 scale;
    scale._data[0][0] = x;
    scale._data[1][1] = y;
    scale._data[2][2] = z;
    return scale;
}

//--------------------------------------------------------------
Mat4 operator * (const Mat4 & a, const Mat4 & b)
{
    Mat4 result;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            float sum = 0;
            for (int k = 0; k < 4; k++)
                sum += a.Data()[i * 4 + k] * b.Data()[k * 4 + j];
            result.Data()[i * 4 + j] = sum;
        }
    return result;
}

