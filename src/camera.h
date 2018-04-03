/*
 * Camera.h
 * Decleration of Camera class
 *
 * Vahid Kazemi
 *********************************************************/

#pragma once

#include "geometry.h"
#include "global.h"
#include "singleton.h"


namespace vrt {

class Camera : public Singleton<Camera> {
public:
  Camera();
  ~Camera();

  void Perspective(float fovy, float aspect, float znear, float zfar);
  void LookAt(const Vector3 &position, const Vector3 &view, const Vector3 &up);
  Ray GetRay(float x, float y);
  void Reset();

private:
  Vector3 pos, dir, up;
  float fovy, aspect, znear, zfar;

  friend class Raytracer;
};

}  // namespace vrt
