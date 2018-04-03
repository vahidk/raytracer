/*
 * Scene.cpp
 * Definition of Scene class
 *
 * Vahid Kazemi
 *********************************************************/

#include "scene.h"

namespace vrt {

Scene::Scene() { objects.clear(); }

void Scene::AddObject(Object *obj) { objects.push_back(obj); }

int Scene::GetObjsNum() { return (int)objects.size(); }

Object *Scene::GetObj(int i) { return objects[i]; }

void Scene::Clear() {
  for (int i = 0; i < (int)objects.size(); i++) {
    delete objects[i];
  }
  objects.clear();

  globalAmbient = 0.1f;
  fog.color = Color(1, 1, 1);
  fog.farDepth = 100;
  fog.nearDepth = 5;
}

void Scene::SetGlobalAmbinet(float ambient) { globalAmbient = ambient; }

void Scene::SetFog(Color color, float n, float f) {
  fog.color = color;
  fog.nearDepth = n;
  fog.farDepth = f;
}

}  // namespace vrt
