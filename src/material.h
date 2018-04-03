/*
 * Material.h
 * decleration of Material class
 *
 * Vahid Kazemi
 *********************************************************/

#pragma once

#include "geometry.h"

namespace vrt {

class Material {
public:
  Material();

  Color color;
  float ambient;
  float diffuse;
  float specular;
  float shininess;
  float emissive;
  float opacity;
  float reflection;
  float refraction;
};

}  // namespace vrt