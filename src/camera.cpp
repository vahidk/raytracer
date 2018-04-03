/*
 * Camera.cpp
 * Definition of Camera class
 *
 * Vahid Kazemi
 *********************************************************/

#include "camera.h"

namespace vrt {

Camera::Camera() { Reset(); }

Camera::~Camera() {}

void Camera::Reset() {
  pos = Vector3(0, 0, 0);
  dir = Vector3(0, 0, 1);
  up = Vector3(1, 0, 0);
  fovy = PI / 2;
  aspect = 1.0f;
  znear = 1.0f;
  zfar = 1000.0f;
}

void Camera::Perspective(float fovy, float aspect, float znear, float zfar) {
  this->fovy = fovy;
  this->aspect = aspect;
  this->znear = znear;
  this->zfar = zfar;
}

void Camera::LookAt(const Vector3 &position, const Vector3 &view,
                    const Vector3 &up) {
  this->pos = position;
  this->dir = (view - position).Normal();
  this->up = up;
}

Ray Camera::GetRay(float x, float y) {
  float my = znear * tanf(fovy / 2.0f);
  float mx = my * aspect;

  const Vector3 &right = (dir.Cross(up)).Normal();
  const Vector3 &rd = (right * 2 * (x - 0.5f) * mx) +
                      ((-up) * 2 * (y - 0.5f) * my) + (dir * znear);

  return Ray(pos, rd);
}
}  // namespace vrt
