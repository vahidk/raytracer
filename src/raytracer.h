/*
 * Raytracer.h
 * Decleration of Raytracer class
 *
 * Vahid Kazemi
 *********************************************************/

#pragma once

#include "camera.h"
#include "scene.h"
#include "singleton.h"
#include "surface.h"


namespace vrt {
class Raytracer : public Singleton<Raytracer> {
public:
  Raytracer();
  ~Raytracer();

  void Initialize(int width, int height);
  void Destroy();

  void GetColorBuffer(RGBA *buffer) const;
  void SaveImage(const char *filename);

  int GetWidth() const { return width; }
  int GetHeight() const { return height; }

  void ResetSettings();
  void ClearBuffers();

  void SetDepth(int depth);
  void SetMaxDistance(float distance);
  void SetSuperSample(int k);
  void SetFog(Color c, float near, float far);
  void SetHDRFilter(int size, float exposure, float power);
  void SetHalfToning() { halfToning = true; }

  void RenderLine(int j);
  void PostProcess();

private:
  void Raytrace(Color &color, const Ray &ray, int depth, float *z = NULL);

  void ApplySupperSample();
  void ApplyFog();
  void ApplyDynamicRangeFiltering();
  void ApplyHalftoning();

  Scene *scene;
  Camera *camera;
  Surface *colorBuffer;
  float *depthBuffer;

  int maxDepth;
  float maxDistance;
  int superSample;
  int width, height;
  int hdrSize;
  float hdrExposure;
  float hdrPower;
  bool halfToning;
};

}  // namespace vrt
