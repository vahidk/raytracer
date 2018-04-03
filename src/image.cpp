/*
 * Image.cpp
 * Definition of Image class
 *
 * Vahid Kazemi
 *********************************************************/

#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace vrt {

Image::Image() {
  width = 0;
  height = 0;
  data = 0;
}

Image::~Image() {
  if (data) {
    free(data);
    data = 0;
  }
}

uint *Image::GetData() { return (uint *)data; }

const uint *Image::GetData() const { return (uint *)data; }

const Color Image::GetPixel(int x, int y) const {
  RGBA &p = ((RGBA *)data)[x + y * width];
  return Color(p);
}

void Image::SetPixel(const Color &c, int x, int y) {
  RGBA &p = ((RGBA *)data)[x + y * width];
  p = RGBA(c);
}

void Image::SetPixel(const RGBA c, int x, int y) {
  RGBA &p = ((RGBA *)data)[x + y * width];
  p = c;
}

bool Image::Load(const char *filename) {
  int w, h, ch;
  stbi_set_flip_vertically_on_load(1);
  uint8_t *data = stbi_load(filename, &w, &h, &ch, 0);
  if (data == nullptr) {
    fprintf(stderr, "Image file not found: %s.", filename);
    return false;
  }

  if (ch != 1 && ch != 3 && ch != 4) {
    fprintf(stderr, "Unsupported image channels: %d", ch);
    return false;
  }

  Create(w, h);
  uint8_t *p = data;
  for (int j = 0; j < h; ++j) {
    for (int i = 0; i < w; ++i) {
      if (ch == 1) {
        SetPixel(RGBA(p[0], p[0], p[0], 255), i, j);
      } else if (ch == 3) {
        SetPixel(RGBA(p[0], p[1], p[2], 255), i, j);
      } else if (ch == 4) {
        SetPixel(RGBA(p[0], p[1], p[2], p[3]), i, j);
      }
      p += ch;
    }
  }
  stbi_image_free(data);
  return true;
}

void Image::Create(int width, int height) {
  this->width = width;
  this->height = height;
  data = (uchar *)malloc(width * height * 4);
}

bool Image::Save(const char *filename) {
  stbi_write_jpg(filename, width, height, 4, data, 100);
  return true;
}

}  // namespace vrt