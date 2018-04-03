/*
 * Surface.cpp
 * Definition of Surface class
 *
 * Vahid Kazemi
 *********************************************************/

#include "surface.h"
#include <string.h>

namespace vrt {

Surface::Surface(int width, int height) {
  this->width = width;
  this->height = height;

  buffer = new Color[width * height];
}

Surface::~Surface() { delete[] buffer; }

const Color *Surface::GetBuffer() const { return buffer; }

Color *Surface::GetBuffer() { return buffer; }

void Surface::Clear(const Color &color) {
  for (int i = 0; i < width * height; i++)
    buffer[i] = color;
}

void Surface::SetPixel(int x, int y, const Color &color) {
  buffer[x + y * width] = color;
}

Color &Surface::GetPixel(int x, int y) { return buffer[x + y * width]; }

void Surface::Blit(int x, int y, const Surface *surface) {
  for (int i = 0; i < surface->GetHeight(); i++) {
    memcpy(buffer + (i + y) * width + x,
           surface->GetBuffer() + i * surface->GetHeight(),
           surface->GetWidth() * sizeof(Color));
  }
}

void Surface::Copy(const Surface *surface) {
  memcpy(buffer, surface->GetBuffer(),
         surface->GetWidth() * surface->GetHeight() * sizeof(Color));
}

// TODO : Implement gausian blur algorithm
void Surface::Blur(int level) {
  if (level <= 0)
    return;

  int halfW = width >> 1, halfH = height >> 1;

  Surface s(halfW, halfH);

  for (int i = 0; i < halfW; i++) {
    for (int j = 0; j < halfH; j++) {
      Color c =
          0.25f * (GetPixel(i << 1, j << 1) + GetPixel(1 + (i << 1), j << 1) +
                   GetPixel(i << 1, 1 + (j << 1)) +
                   GetPixel(1 + (i << 1), 1 + (j << 1)));

      s.SetPixel(i, j, c);
    }
  }

  s.Blur(level - 1);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      GetPixel(i, j) =
          GetPixel(i, j) * 0.25f + s.GetPixel(i >> 1, j >> 1) * 0.75f;
    }
  }
}

} // namespace vrt