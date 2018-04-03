/*
 * Texture.cpp
 * Definition of CheckerTexture, WoodTexture, NoiseTexture
 * and ImageTexture
 *
 * Vahid Kazemi
 *********************************************************/

#include "texture.h"

namespace vrt {

// Checker Texture

Color CheckerTexture::GetColor(Vector3 point) {
  int x = PFMOD(point.x, 1.0f) > 0.5f ? 1 : -1;
  int y = PFMOD(point.y, 1.0f) > 0.5f ? 1 : -1;
  int z = PFMOD(point.z, 1.0f) > 0.5f ? 1 : -1;

  if (x * y * z > 0)
    return Color(1, 1, 1);

  return Color(0, 0, 0);
}

// WoodTexture

Color WoodTexture::GetColor(Vector3 point) {
  const Color A(0.7f, 0.5f, 0.1f);
  const Color D(0.9f, 0.9f, 0.4f);
  const float M = .1f;
  float r = sqrtf(point.x * point.x + point.y * point.y);
  float v = r / M;
  int rings = ((int)v) % 2;
  return D + (A * (float)rings);
}

// NoiseTexture

Color NoiseTexture::GetColor(Vector3 point) { return Color(0, 0, 0); }

// ImageTexture

ImageTexture::ImageTexture(const char *filename) {
  if (!image.Load(filename))
    fprintf(stderr, "Unable to load the texure %s\n", filename);
}

Color ImageTexture::GetColor(Vector3 point) {
  int tx = (int)(PFMOD(point.x, 1) * image.GetWidth());
  int ty = (int)(PFMOD(point.y, 1) * image.GetHeight());

  return image.GetPixel(tx, ty);
}

} // namespace vrt
