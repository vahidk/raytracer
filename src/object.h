/*
 * Object.h
 * Decleration of Object abstract class, SphereObject and
 * PlaneObject classes
 *
 * Vahid Kazemi
 *********************************************************/

#pragma once

#include "geometry.h"
#include "mapping.h"
#include "material.h"
#include "texture.h"


namespace vrt {

enum InterType {
  INTER_NONE,
  INTER_HIT,
  INTER_INSIDE,
};

class Object {
public:
  Object();
  virtual ~Object();

  virtual InterType Intersect(const Ray &ray, float &length,
                              Vector3 &normal) const = 0;
  virtual const Vector3 GetCenter() const = 0;

  Material *GetMaterial(); // provides direct access to material properties

  const Color GetTexColor(const Vector3 &point);

  void SetTexture(Texture *texture);
  void SetMapping(Mapping *map);

  void SetLight();
  bool IsLight() const;

protected:
  Texture *texture;
  Mapping *mapping;
  Material material;
  bool light;
};

class SphereObject : public Object, public Sphere {
public:
  SphereObject();
  SphereObject(const Vector3 &origin, float radius);

  InterType Intersect(const Ray &ray, float &length, Vector3 &normal) const;
  const Vector3 GetCenter() const;
};

class PlaneObject : public Object, public Plane {
public:
  PlaneObject();
  PlaneObject(const Vector3 &normal, float d);

  InterType Intersect(const Ray &ray, float &length, Vector3 &normal) const;
  const Vector3 GetCenter() const;
};

}  // namespace vrt
