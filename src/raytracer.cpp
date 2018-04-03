/*
 * Raytracer.cpp
 * Definition of Raytracer class
 *
 * Vahid Kazemi
 *********************************************************/

#include "raytracer.h"
#include "image.h"

namespace vrt {

Raytracer::Raytracer() {
  depthBuffer = NULL;
  colorBuffer = NULL;
}

Raytracer::~Raytracer() { Destroy(); }

void Raytracer::Initialize(int width, int height) {
  scene = Scene::GetInstance();
  camera = Camera::GetInstance();

  this->width = width;
  this->height = height;

  Destroy();

  colorBuffer = new Surface(width, height);
  depthBuffer = new float[width * height];

  ResetSettings();

  ClearBuffers();
}

void Raytracer::Destroy() {
  if (depthBuffer)
    delete[] depthBuffer;

  if (colorBuffer)
    delete colorBuffer;
}

void Raytracer::ResetSettings() {
  hdrSize = 32;
  hdrExposure = 0;
  hdrPower = 2;
  maxDepth = 8;
  maxDistance = 1000.0f;
  superSample = 1;
  halfToning = false;
  scene->fog.enable = false;
  camera->Reset();
}

void Raytracer::SetDepth(int depth) { maxDepth = depth; }

void Raytracer::SetMaxDistance(float distance) { maxDistance = distance; }

void Raytracer::SetSuperSample(int k) { superSample = k; }

void Raytracer::SetFog(Color c, float nearDepth, float farDepth) {
  scene->fog.enable = true;
  scene->fog.color = c;
  scene->fog.nearDepth = nearDepth;
  scene->fog.farDepth = farDepth;
}

void Raytracer::SetHDRFilter(int size, float exposure, float power) {
  hdrSize = size;
  hdrExposure = exposure;
  hdrPower = power;
}

void Raytracer::GetColorBuffer(RGBA *buffer) const {
  for (int j = 0; j < colorBuffer->GetHeight(); j++) {
    for (int i = 0; i < colorBuffer->GetWidth(); i++) {
      buffer[i + j * colorBuffer->GetWidth()] =
          RGBA(colorBuffer->GetPixel(i, j));
    }
  }
}

void Raytracer::SaveImage(const char *filename) {
  std::vector<RGBA> buffer(width * height);
  GetColorBuffer(buffer.data());

  Image img;
  img.Create(width, height);

  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      img.SetPixel(buffer[i + j * width], i, j);
    }
  }
  img.Save(filename);
}

void Raytracer::RenderLine(int j) {
  Color color;

  for (int i = 0; i < width; i++) {
    Raytrace(color, camera->GetRay((float)i / width, (float)j / height),
             maxDepth, &depthBuffer[i + j * width]);
    colorBuffer->SetPixel(i, j, color);
  }
}

void Raytracer::Raytrace(Color &color, const Ray &ray, int depth, float *z) {
  float length = maxDistance;
  InterType it, tmpIt;
  Object *obj = 0;
  Vector3 norm;

  for (int i = 0; i < scene->GetObjsNum(); i++) {
    Object *tmpObj = scene->GetObj(i);
    if ((tmpIt = tmpObj->Intersect(ray, length, norm)) != INTER_NONE) {
      it = tmpIt;
      obj = tmpObj;
    }
  }

  if (obj) {
    const Material *mat = obj->GetMaterial();
    Color crfl(0, 0, 0), crfr(0, 0, 0), cdif(0, 0, 0), cspc(0, 0, 0);
    const Vector3 &hitPoint1 = ray.origin + ray.direction * (length - EPSILON);
    const Vector3 &hitPoint2 = ray.origin + ray.direction * (length + EPSILON);

    if (z != NULL)
      *z = length;

    switch (it) {
    case INTER_HIT:

      if (depth > 1) {
        if (mat->reflection > 0.0f) {
          Raytrace(crfl, Ray(hitPoint1, ray.direction.Reflection(norm)),
                   depth - 1);
        }
        if (mat->opacity < 1.0f) {
          Raytrace(
              crfr,
              Ray(hitPoint2, ray.direction.Refraction(norm, mat->refraction)),
              depth - 1);
        }
      }

      for (int i = 0; i < scene->GetObjsNum(); i++) {
        Object *lo = scene->GetObj(i);
        if (lo->IsLight()) // This is a light!
        {
          bool lit = true;
          Vector3 lnorm; // For no use!!
          Vector3 ldir = lo->GetCenter() - hitPoint1;
          Color lc(1, 1, 1);
          float ldist = (ldir).Length();

          for (int k = 0; k < scene->GetObjsNum(); k++) {
            Object *to = scene->GetObj(k);
            if (to != lo && to->Intersect(Ray(hitPoint1, ldir), ldist, lnorm) !=
                                INTER_NONE) {
              const Material *tm = to->GetMaterial();

              if (tm->opacity < 1) {
                lc = lc * (1 - tm->opacity) +
                     tm->color.Modulate(lc) * tm->opacity;
              } else {
                lit = false;
                break;
              }
            }
          }

          if (lit) {
            const Material *lm = lo->GetMaterial();
            Color lcolor = lm->emissive * lm->color.Modulate(lc);
            cdif +=
                lcolor.Modulate(mat->color) * SATURATE(ldir.Normal().Dot(norm));
            Vector3 h = (ldir.Normal() - ray.direction).Normal();
            cspc += lcolor * powf(SATURATE(h.Dot(norm)), mat->shininess);
          }
        }
      }

      color = (mat->color * mat->emissive) +
              (cdif * mat->diffuse +
               mat->color * scene->globalAmbient * mat->ambient)
                  .Modulate(obj->GetTexColor(hitPoint1 - obj->GetCenter())) +
              (cspc * mat->specular) + (crfl * mat->reflection) +
              (crfr * (1 - mat->opacity));
      break;
    case INTER_INSIDE:
      if (depth > 1) {
        if (mat->opacity < 1.0f) {
          Raytrace(crfl,
                   Ray(hitPoint2,
                       ray.direction.Refraction(norm, 1 / mat->refraction)),
                   depth - 1);
        }
      }
      color = crfl * (1 - mat->opacity);
      break;
    default:
      break;
    }
  } else {
    color.Set(0, 0, 0);
  }
}

void Raytracer::ClearBuffers() {
  colorBuffer->Clear(Color(0, 0, 0));

  for (int k = 0; k < width * height; k++)
    depthBuffer[k] = camera->zfar;
}

void Raytracer::ApplyFog() {
  Color c;

  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      float &dp = depthBuffer[i + j * width];

      if (dp < scene->fog.nearDepth) {
        c = colorBuffer->GetPixel(i, j);
      } else if (dp > scene->fog.farDepth) {
        c = scene->fog.color;
      } else {
        float d = (dp - scene->fog.nearDepth) /
                  (scene->fog.farDepth - scene->fog.nearDepth);
        c = (colorBuffer->GetPixel(i, j) * (1 - d)) + (scene->fog.color * d);
      }

      colorBuffer->SetPixel(i, j, c);
    }
  }
}

void Raytracer::ApplySupperSample() {
  Surface tmpSurface(width, height);
  tmpSurface.Copy(colorBuffer);

  Color c;

  for (int j = superSample; j < height - superSample; j++) {
    for (int i = superSample; i < width - superSample; i++) {
      c.Set(0, 0, 0);

      for (int ki = -superSample; ki < superSample; ki++) {
        for (int kj = -superSample; kj < superSample; kj++) {
          c += tmpSurface.GetPixel(i + ki, j + kj);
        }
      }

      c /= (float)(4 * superSample * superSample);
      colorBuffer->SetPixel(i, j, c);
    }
  }
}

void Raytracer::ApplyDynamicRangeFiltering() {
  int sw = colorBuffer->GetWidth(), sh = colorBuffer->GetHeight();

  int totalPixels = sw * sh;

  float *hdrBuffer = new float[totalPixels];
  float *tmpBuffer = new float[totalPixels];

  for (int i = 0; i < sw; i++) {
    for (int j = 0; j < sh; j++) {
      Color c = colorBuffer->GetPixel(i, j);
      hdrBuffer[i + j * sw] = powf(
          (0.299f * c.r + 0.587f * c.g + 0.184f * c.b) * hdrExposure, hdrPower);
    }
  }

  for (int k = 0; k < hdrSize; k++) {
    memcpy(tmpBuffer, hdrBuffer, totalPixels * sizeof(float));

    for (int i = 1; i < sw - 1; i++) {
      for (int j = 1; j < sh - 1; j++) {
        hdrBuffer[i + j * sw] =
            (tmpBuffer[i - 1 + (j - 1) * sw] + tmpBuffer[i + (j - 1) * sw] +
             tmpBuffer[i + 1 + (j - 1) * sw] + tmpBuffer[i - 1 + j * sw] +
             tmpBuffer[i + j * sw] + tmpBuffer[i + 1 + j * sw] +
             tmpBuffer[i - 1 + (j + 1) * sw] + tmpBuffer[i + (j + 1) * sw] +
             tmpBuffer[i + 1 + (j + 1) * sw]) /
            9;
      }
    }
  }

  for (int i = 0; i < sw; i++) {
    for (int j = 0; j < sh; j++) {
      float d = hdrBuffer[i + j * sw];
      colorBuffer->GetPixel(i, j) += Color(d, d, d);
    }
  }
}

void Raytracer::ApplyHalftoning() {
  int width = colorBuffer->GetWidth(), height = colorBuffer->GetHeight();

  float *s = new float[width * height];
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      s[i + j * width] = colorBuffer->GetPixel(i, j).GrayScale();
    }
  }

  colorBuffer->Clear(Color(0, 0, 0));

  for (int j = height - 1; j >= 1; j--) {
    for (int i = 1; i < width; i++) {
      float c = s[i + j * width];
      float k = (float)((int)(c + 0.5f));
      float e = c - k;

      s[(i + 1) + (j)*width] += e * 7 / 16;
      s[(i - 1) + (j - 1) * width] += e * 3 / 16;
      s[(i) + (j - 1) * width] += e * 5 / 16;
      s[(i + 1) + (j - 1) * width] += e * 1 / 16;

      colorBuffer->SetPixel(i, j, Color(k, k, k));
    }
  }
}

void Raytracer::PostProcess() {
  if (scene->fog.enable)
    ApplyFog();

  if (hdrExposure > 0)
    ApplyDynamicRangeFiltering();

  if (superSample > 0)
    ApplySupperSample();

  if (halfToning)
    ApplyHalftoning();
}

}  // namespace vrt