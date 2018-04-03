/*
 * Scene.h
 * Decleration of Scene class
 *
 * Vahid Kazemi
 *********************************************************/

#pragma once

#include "geometry.h"
#include "object.h"
#include "singleton.h"


namespace vrt {

struct Fog {
  Color color;
  float nearDepth;
  float farDepth;
  bool enable;
};

class Scene : public Singleton<Scene> {
public:
  Scene();

  void AddObject(Object *object);
  int GetObjsNum();
  Object *GetObj(int i);
  void Clear();

  void SetGlobalAmbinet(float ambient);
  void SetFog(Color color, float near, float far);

private:
  std::vector<Object *> objects;
  float globalAmbient;
  Fog fog;

  friend class Raytracer;
};

}  // namespace vrt
