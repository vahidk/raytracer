/*
 * Material.cpp
 * Definition of Material class
 *
 * Vahid Kazemi
 *********************************************************/

#include "material.h"

namespace vrt {

Material::Material() {
  color = Color(1, 1, 1);
  ambient = 0.0f;
  diffuse = 1.0f;
  specular = 0.0f;
  shininess = 8.0f;
  emissive = 0.0f;
  reflection = 0.0f;
  opacity = 1.0f;
  refraction = 1.0f;
}

}  // namespace vrt