/*
 * image.h
 * Decleration of Image class
 *
 * Vahid Kazemi
 *********************************************************/

#pragma once

#include "geometry.h"
#include "global.h"

namespace vrt {

struct RGBA {
  RGBA() = default;
  explicit RGBA(uint rgba) : rgba(rgba) {}
  RGBA(uchar r, uchar g, uchar b, uchar a) : r(r), g(g), b(b), a(a) {}
  RGBA(const Color &c)
      : r(SATURATE(c.r) * 255), g(SATURATE(c.g) * 255), b(SATURATE(c.b) * 255),
        a(255) {}

  operator Color() { return Color(r / 255.f, g / 255.f, b / 255.f); }

  union {
    struct {
      uchar r, g, b, a;
    };
    uint rgba;
  };
};

class Image {
public:
  Image();
  ~Image();

  bool Load(const char *filename);
  void Create(int width, int height);
  bool Save(const char *filename);

  const uint *GetData() const;
  uint *GetData();

  const Color GetPixel(int x, int y) const;
  void SetPixel(const Color &c, int x, int y);
  void SetPixel(const RGBA c, int x, int y);

  uint GetWidth() { return width; }
  uint GetHeight() { return height; }

private:
  uint width;
  uint height;
  uchar *data;
};

}  // namespace vrt
