/*
 * Object.cpp
 * Definition of Object class
 *
 * Vahid Kazemi
 *********************************************************/

#include "object.h"
#include "mapping.h"

namespace vrt {

// OBJECT ///////////////////////////////////////////////////////////////////

Object::Object() {
  texture = 0;
  mapping = 0;
}

Object::~Object() {
  if (mapping)
    delete mapping;

  if (texture)
    delete texture;
}

Material *Object::GetMaterial() { return &material; }

void Object::SetLight() { light = true; }

bool Object::IsLight() const { return light; }

const Color Object::GetTexColor(const Vector3 &point) {
  if (texture == 0)
    return Color(1, 1, 1);

  if (mapping == 0)
    mapping = new CubeMapping(1, 1, 1);

  return texture->GetColor(mapping->GetTexCoord(point));
}

void Object::SetTexture(Texture *texture) { this->texture = texture; }

void Object::SetMapping(Mapping *map) { this->mapping = map; }

// SPHEREOBJECT //////////////////////////////////////////////////////////

SphereObject::SphereObject() {}

SphereObject::SphereObject(const Vector3 &origin, float radius)
    : Sphere(origin, radius) {}

InterType SphereObject::Intersect(const Ray &ray, float &length,
                                  Vector3 &norm) const {
  Vector3 rv = ray.direction * length;

  float a = length * length;
  float b = 2 * rv.Dot(ray.origin - origin);
  float c = origin.SqrLen() + ray.origin.SqrLen() -
            2 * (origin.Dot(ray.origin)) - radius * radius;
  float d = b * b - 4 * a * c;

  if (d <= 0)
    return INTER_NONE;

  float t1 = (-b - sqrtf(d)) / (2 * a), t2 = (-b + sqrtf(d)) / (2 * a);

  if (t1 >= 1 || t2 <= 0) {
    return INTER_NONE;
  }

  if (t1 <= 0) {
    length *= t2;
    norm = -((length * ray.direction) + ray.origin - origin).Normal();
    return INTER_INSIDE;
  }

  length *= t1;
  norm = ((length * ray.direction) + ray.origin - origin).Normal();
  return INTER_HIT;
}

const Vector3 SphereObject::GetCenter() const { return origin; }

// PLANEOBJECT ////////////////////////////////////////////////////////////////

PlaneObject::PlaneObject() {}

PlaneObject::PlaneObject(const Vector3 &normal, float d) : Plane(normal, d) {}

InterType PlaneObject::Intersect(const Ray &ray, float &length,
                                 Vector3 &norm) const {
  float dp = normal.Dot(ray.direction);

  if (dp == 0.0f) {
    return INTER_NONE;
  }

  float t = (d - normal.Dot(ray.origin)) / (dp * length);

  if (t > 1.0f || t < 0.0f) {
    return INTER_NONE;
  }

  length *= t;
  norm = normal;

  if (dp > 0) {
    norm *= -1;
    return INTER_INSIDE;
  }

  return INTER_HIT;
}

const Vector3 PlaneObject::GetCenter() const { return Vector3(0, 0, 0); }

}  // namespace vrt
