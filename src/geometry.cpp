/*
 * Geometry.cpp
 * Definition of geometry tools
 *
 * Vahid Kazemi
 *********************************************************/

#include "geometry.h"

namespace vrt {

// VECTOR3 //////////////////////////////////////////////////////////////////

void Vector3::Set(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector3 Vector3::operator+(const Vector3 &vec) const {
  return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

const Vector3 &Vector3::operator+=(const Vector3 &vec) {
  x += vec.x;
  y += vec.y;
  z += vec.z;
  return *this;
}

Vector3 Vector3::operator-(const Vector3 &vec) const {
  return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

const Vector3 &Vector3::operator-=(const Vector3 &vec) {
  x -= vec.x;
  y -= vec.y;
  z -= vec.z;
  return *this;
}

Vector3 Vector3::operator/(float s) const {
  return Vector3(x / s, y / s, z / s);
}

const Vector3 &Vector3::operator/=(float s) {
  x /= s;
  y /= s;
  z /= s;
  return *this;
}

Vector3 Vector3::operator*(float s) const {
  return Vector3(x * s, y * s, z * s);
}

Vector3 operator*(float s, const Vector3 &vec) {
  return Vector3(vec.x * s, vec.y * s, vec.z * s);
}

const Vector3 &Vector3::operator*=(float s) {
  x *= s;
  y *= s;
  z *= s;
  return *this;
}

Vector3 Vector3::operator-() const { return Vector3(-x, -y, -z); }

float Vector3::Dot(const Vector3 &vec) const {
  return x * vec.x + y * vec.y + z * vec.z;
}

float Vector3::Length() const { return sqrtf(x * x + y * y + z * z); }

float Vector3::SqrLen() const { return x * x + y * y + z * z; }

Vector3 Vector3::Normal() const { return *this / Length(); }

float Vector3::Distance(const Vector3 &vec) const {
  return (*this - vec).Length();
}

Vector3 Vector3::Reflection(const Vector3 &N) const {
  return *this - 2 * (N.Dot(*this)) * N;
}

Vector3 Vector3::Refraction(const Vector3 &N, float r) const {
  Vector3 L = -*this;
  float NL = N.Dot(L);
  float ct = sqrtf(1 - (r * r) * (1 - (NL * NL)));
  return (r * NL - ct) * N - r * L;
}

Vector3 Vector3::Cross(const Vector3 &vec) const {
  return Vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z,
                 x * vec.y - y * vec.x);
}

Vector3 Color::Modulate(const Vector3 &vec) const {
  return Vector3(x * vec.x, y * vec.y, z * vec.z);
}

float Color::GrayScale() const { return 0.3f * x + 0.4f * y + 0.3f * z; }

// PLANE //////////////////////////////////////////////////////////////////

Plane::Plane() {}

Plane::Plane(const Vector3 &normal, float d) {
  this->normal = normal.Normal();
  this->d = d;
}

// SPHERE //////////////////////////////////////////////////////////////////

Sphere::Sphere() {}

Sphere::Sphere(const Vector3 &origin, float radius) {
  this->origin = origin;
  this->radius = radius;
}

// RAY //////////////////////////////////////////////////////////////////

Ray::Ray() {}

Ray::Ray(const Vector3 &origin, const Vector3 &direction) {
  this->origin = origin;
  this->direction = direction.Normal();
}

}  // namespace vrt