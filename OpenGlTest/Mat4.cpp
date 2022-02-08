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

Mat4 Mat4::Projection(float aspect, float fov, float near, float far)
{
    _data[0][0] = 1 / (aspect * tan(fov / 2));
    _data[1][1] = 1 / (tan(fov / 2));
    _data[2][2] = (far + near) / (far - near);
    _data[2][3] = (2 * far * near) / (far - near);
    _data[3][2] = -1;
    return *this;
}

//--------------------------------------------------------------
Mat4 Mat4::Rotate(float angle, float x, float y, float z)
{
    Mat4 matX;
    Mat4 matY;
    Mat4 matZ;

    matX._data[1][1] = (cosf(angle) * x);
    matX._data[2][1] = (-sinf(angle) * x);                  
    matX._data[1][2] = (sinf(angle) * x);
    matX._data[2][2] = (cosf(angle) * x);


    matY._data[0][0] = (cosf(angle) * y);
    matY._data[2][0] = (sinf(angle) * y); 
    matY._data[0][2] = (sinf(angle) * y);
    matY._data[2][2] = (cosf(angle) * y);

    matZ._data[0][0] = (cos(angle) * z);
    matZ._data[1][0] = (-sinf(angle) * z);
    matZ._data[0][1] = (sinf(angle) * z);
    matZ._data[1][1] = (cosf(angle) * z);


    Multiply(matX);
    Multiply(matY);
    Multiply(matZ);

    



    //Mat4 mat;
    //mat._data[0][0] += (cosf(angle) * y) * (cos(angle) * z);
    //mat._data[1][0] += (-sinf(angle) * z);
    //mat._data[2][0] += (sinf(angle) * y);

    //mat._data[0][1] += (sinf(angle) * z);
    //mat._data[1][1] += (cosf(angle) * x) * (cosf(angle) * z);
    //mat._data[2][1] += (-sinf(angle) * x);

    //mat._data[0][2] += (sinf(angle) * y);
    //mat._data[1][2] += (sinf(angle) * x);
    //mat._data[2][2] += (cosf(angle) * x) * (cosf(angle) * y);

    //this->Multiply(mat);





    //https://www.cprogramming.com/tutorial/3d/rotation.html and https://learnopengl.com/Getting-started/Transformations
    //tX2 + c         tXY - sZ        tXZ + sY        0              
    //tXY+sZ          tY2 + c         tYZ - sX        0               
    //tXZ - sY        tYZ + sX        tZ2 + c         0
    // 
    //Mat4 matRot;
    //float t = 1 - cosf(angle);
    //float s = 1 - sinf(angle);
    //float c = cosf(angle);
    ////tX2 + c         tXY - sZ        tXZ + sY        0 
    //matRot._data[0][0] += t * x * x + c;
    //matRot._data[1][0] += t * x * y - s * z;
    //matRot._data[2][0] += t * x * z + s * y;

    ////tXY+sZ          tY2 + c         tYZ - sX        0 
    //matRot._data[0][1] += t * x * y + s * z;
    //matRot._data[1][1] += t * y * y + c;
    //matRot._data[2][1] += t * y * z - s * x;

    ////tXZ - sY        tYZ + sX        tZ2 + c         0
    //matRot._data[0][1] += t * x * z - s * y;
    //matRot._data[1][1] += t * y * z + s * x;
    //matRot._data[2][1] += t * z * z + c;
    //this->Multiply(matRot);
    return *this;
}

//--------------------------------------------------------------
Mat4 Mat4::Translate(float x, float y, float z)
{
    _data[3][0] += x;
    _data[3][1] += y;
    _data[3][2] += z;
    return *this;
}

//--------------------------------------------------------------
Mat4 Mat4::Multiply(Mat4 mat)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            float sum = 0;
            for (int k = 0; k < 4; k++)
                sum += _data[i][k] * mat._data[k][j];
            _data[i][j] = sum;
        }
    return *this;
}

//--------------------------------------------------------------
Mat4 Mat4::Scale(float x, float y, float z)
{
    _data[0][0] = _data[0][0] * x;
    _data[1][1] = _data[1][1] * y;
    _data[2][2] = _data[2][2] * z;
    return *this;
}

