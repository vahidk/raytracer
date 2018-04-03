/*
 * Surface.h
 * Decleration of Surface class
 *
 * Vahid Kazemi
 *********************************************************/

#pragma once

#include "geometry.h"
#include "global.h"


namespace vrt {

class Surface {
public:
  Surface(int width, int height);
  ~Surface();

  const Color *GetBuffer() const;
  Color *GetBuffer();

  void Clear(const Color &color);

  void SetPixel(int x, int y, const Color &color);
  Color &GetPixel(int x, int y);

  void Blit(int x, int y, const Surface *surface);
  void Copy(const Surface *surface);

  void Blur(int level);

  int GetWidth() const { return width; }

  int GetHeight() const { return height; }

private:
  int width;
  int height;
  Color *buffer;
};

}  // namespace vrt