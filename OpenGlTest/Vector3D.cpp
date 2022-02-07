#include "Vector3D.h"
#include "Math.h"

//--------------------------------------------------------------
Vector3D::Vector3D(float x, float y, float z)
{
    _data[0] = x;
    _data[1] = y;
    _data[2] = z;
}

//--------------------------------------------------------------
Vector3D::Vector3D(float * xyz)
{
    for (int i = 0; i < 3; i++)
        _data[i] = xyz[i];
}

//--------------------------------------------------------------
float Vector3D::X() const
{
    return _data[0];
}

//--------------------------------------------------------------
float Vector3D::Y() const
{
    return _data[1];
}

//--------------------------------------------------------------
float Vector3D::Z() const
{
    return _data[2];
}

//--------------------------------------------------------------
float Vector3D::Length()
{
    return sqrtf(X() * X() + Y() * Y() + Z() * Z());
}

//--------------------------------------------------------------
void Vector3D::Normalize()
{
    float length = Length();
    for(int i = 0; i < 3; i++)
        _data[i] = _data[i] / length;
}

//--------------------------------------------------------------
Vector3D Vector3D::CrossProduct(const Vector3D & a, const Vector3D & b)
{
    Vector3D result(
        a.Y() * b.Z() - a.Z() * b.Y(),  //X
      -(a.Z() * b.X() - a.X() * b.Z()), //Y
        a.X() * b.Y() - a.Y() * b.X()   //Z
    );
    return result;
}

//--------------------------------------------------------------
Vector3D Vector3D::operator - (const Vector3D & rhs) const
{
    return Vector3D(X() - rhs.X(), Y() - rhs.Y(), Z() - rhs.Z());
}

////--------------------------------------------------------------
//Vector3D Vector3D::operator * (const Vector3D & rhs) const
//{
//    return Vector3D(X() * rhs.X(), Y() * rhs.Y(), Z() * rhs.Z());
//}
//
//--------------------------------------------------------------
Vector3D Vector3D::operator * (const float rhs) const
{
    return Vector3D(X() * rhs, Y() * rhs, Z() * rhs);
}



