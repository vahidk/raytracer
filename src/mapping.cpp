/*
 * Mapping.cpp
 * Definition of CubeMapping, CylindarMapping and
 * SphereMapping classes
 *
 * Vahid Kazemi
 *********************************************************/

#include "mapping.h"

namespace vrt {

// CubeMapping

CubeMapping::CubeMapping(float xScale, float yScale, float zScale) {
  this->xScale = xScale;
  this->yScale = yScale;
  this->zScale = zScale;
}

const TexCoord CubeMapping::GetTexCoord(const Vector3 &vec) {
  return TexCoord(vec.x * xScale, vec.y * yScale, vec.z * zScale);
}

// CylindarMapping

CylinderMapping::CylinderMapping(float rounds, float zScale) {
  this->rounds = rounds;
  this->zScale = zScale;
}

const TexCoord CylinderMapping::GetTexCoord(const Vector3 &vec) {
  return TexCoord(rounds * vec.Teta() / PIx2, vec.z * zScale, 0);
}

// SphereMapping

SphereMapping::SphereMapping(float rounds) { this->rounds = rounds; }

const TexCoord SphereMapping::GetTexCoord(const Vector3 &vec) {
  return TexCoord(rounds * vec.Teta() / PIx2, rounds * vec.Phi() / PIx2, 0);
}

}  // namespace vrt
