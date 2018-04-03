/*
 * geometry.h
 * Decleration of geometry tools, including Vector3,
 * Vector2, Plane, Sphere and Ray classes
 *
 * Vahid Kazemi
 *********************************************************/

#pragma once

#include "global.h"

namespace vrt {

class Vector3 {
public:
  Vector3() {}
  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

  void Set(float x, float y, float z);
  const Vector3 operator+(const Vector3 &vec) const;
  const Vector3 &operator+=(const Vector3 &vec);
  const Vector3 operator-(const Vector3 &vec) const;
  const Vector3 &operator-=(const Vector3 &vec);
  const Vector3 operator/(float s) const;
  const Vector3 &operator/=(float s);
  const Vector3 operator*(float s) const;
  friend const Vector3 operator*(float s, const Vector3 &vec);
  const Vector3 &operator*=(float s);
  const Vector3 operator-() const;
  float Dot(const Vector3 &vec) const;
  float Length() const;
  float SqrLen() const;
  const Vector3 Normal() const;
  float Distance(const Vector3 &vec) const;
  const Vector3 Reflection(const Vector3 &normal) const;
  const Vector3 Refraction(const Vector3 &normal, float ratio) const;
  const Vector3 Cross(const Vector3 &vec) const;
  const Vector3 Modulate(const Vector3 &color) const;
  const float GrayScale() const;

  float Teta() const {
    float r = sqrtf(x * x + y * y);
    float teta = acosf(x / r);
    if (y < 0) {
      return -teta;
    }
    return teta;
  }

  float Phi() const {
    float r = sqrtf(x * x + z * z);
    float phi = acosf(z / r);
    if (x < 0) {
      return -phi;
    }
    return phi;
  }

  union {
    struct {
      float x, y, z;
    };
    struct {
      float r, g, b;
    };
    struct {
      float v[3];
    };
  };
};

typedef Vector3 Color;
typedef Vector3 TexCoord;

class Vector2 {
public:
  Vector2() {}

  Vector2(float x, float y) {
    this->x = x;
    this->y = y;
  }

  const Vector2 operator+(const Vector2 &vec) const {
    return Vector2(x + vec.x, y + vec.y);
  }

  const Vector2 operator-(const Vector2 &vec) const {
    return Vector2(x - vec.x, y - vec.y);
  }

  const Vector2 operator*(const float f) const { return Vector2(x * f, y * f); }

  const Vector2 operator/(const float f) const { return Vector2(x / f, y / f); }

  union {
    struct {
      float x, y;
    };
    struct {
      float v[2];
    };
  };
};

class Plane {
public:
  Plane();
  Plane(const Vector3 &normal, float d);

  Vector3 normal;
  float d;
};

class Sphere {
public:
  Sphere();
  Sphere(const Vector3 &origin, float radius);

  Vector3 origin;
  float radius;
};

class Ray {
public:
  Ray();
  Ray(const Vector3 &origin, const Vector3 &direction);

  Vector3 origin;
  Vector3 direction;
};

}  // namespace vrt
