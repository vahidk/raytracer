/*
 * texture.h
 * Decleration of Texture abstract class, CheckerTexture,
 * WoodTexture, NoiseTexture and ImageTexture classes
 *
 * Vahid Kazemi
 *********************************************************/

#pragma once

#include "geometry.h"
#include "image.h"

namespace vrt {

class Texture {
public:
  Texture() {}
  virtual ~Texture() {}

  virtual Color GetColor(Vector3 point) = 0;
};

class CheckerTexture : public Texture {
public:
  Color GetColor(Vector3 point);
};

class WoodTexture : public Texture {
public:
  Color GetColor(Vector3 point);
};

class NoiseTexture : public Texture {
public:
  Color GetColor(Vector3 point);
};

class ImageTexture : public Texture {
public:
  ImageTexture(const char *filename);

  Color GetColor(Vector3 point);

private:
  Image image;
};

}  // namespace vrt