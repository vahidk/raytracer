/*
 * mapping.h
 * decleration of Mapping abstract class, CubeMapping,
 * CylindarMapping and SphereMapping
 *
 * Vahid Kazemi
 *********************************************************/

#pragma once

#include "geometry.h"

namespace vrt {

class Mapping {
public:
  Mapping() {}
  virtual ~Mapping() {}

  virtual const TexCoord GetTexCoord(const Vector3 &position) = 0;
};

class CubeMapping : public Mapping {
public:
  CubeMapping(float xScale, float yScale, float zScale);

  const TexCoord GetTexCoord(const Vector3 &position);

private:
  float xScale, yScale, zScale;
};

class CylinderMapping : public Mapping {
public:
  CylinderMapping(float rounds, float zScale);

  const TexCoord GetTexCoord(const Vector3 &position);

private:
  float rounds;
  float zScale;
};

class SphereMapping : public Mapping {
public:
  SphereMapping(float rounds);

  const TexCoord GetTexCoord(const Vector3 &position);

private:
  float rounds;
};

}  // namespace vrt