#pragma once

class Vector3D
{
public:
    Vector3D(float x, float y, float z);
    Vector3D(float * xyz);
    float Length();
    void Normalize();
    float * Data() { return _data; };
    float X() const;
    float Y() const;
    float Z() const;
    static Vector3D CrossProduct(const Vector3D & a, const Vector3D & b);
    static Vector3D Normal(const Vector3D& a, const Vector3D& b, const Vector3D& c);
    Vector3D operator - (const Vector3D & rhs) const;
    //Vector3D operator * (const Vector3D & rhs) const;
    Vector3D operator * (const float rhs) const;
private:
    float _data[3];
};

