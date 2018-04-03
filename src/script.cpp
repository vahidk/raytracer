/*
 * Script.cpp
 * Definition of Script class
 *
 * Vahid Kazemi
 *********************************************************/

#include "script.h"
#include "concurrency.h"

namespace vrt {

// Lua Interface Functions ///////////////////////////////////////////////

int init(lua_State *ls) {
  int width = (int)lua_tonumber(ls, 1);
  int height = (int)lua_tonumber(ls, 2);

  Raytracer::GetInstance()->Initialize(width, height);

  return 0;
}

int clear(lua_State *) {
  Scene::GetInstance()->Clear();
  return 0;
}

int render(lua_State *ls) {
  const char *filename = lua_tostring(ls, 1);

  Raytracer *raytracer = Raytracer::GetInstance();

  raytracer->ClearBuffers();

  int lines = raytracer->GetHeight();
  ParallelFor(0, lines, [&](int i) { raytracer->RenderLine(i); });

  raytracer->PostProcess();

  raytracer->SaveImage(filename);

  return 0;
}

int createSphere(lua_State *ls) {
  Vector3 origin;
  origin.x = (float)lua_tonumber(ls, 1);
  origin.y = (float)lua_tonumber(ls, 2);
  origin.z = (float)lua_tonumber(ls, 3);

  float r = (float)lua_tonumber(ls, 4);

  Object *obj = new SphereObject(origin, r);
  Scene::GetInstance()->AddObject(obj);

  lua_pushlightuserdata(ls, obj);

  return 1;
}

int createPlane(lua_State *ls) {
  Vector3 normal;
  normal.x = (float)lua_tonumber(ls, 1);
  normal.y = (float)lua_tonumber(ls, 2);
  normal.z = (float)lua_tonumber(ls, 3);

  float d = (float)lua_tonumber(ls, 4);

  Object *obj = new PlaneObject(normal, d);
  Scene::GetInstance()->AddObject(obj);

  lua_pushlightuserdata(ls, obj);

  return 1;
}

int setGlobalAmbient(lua_State *ls) {
  Scene::GetInstance()->SetGlobalAmbinet((float)lua_tonumber(ls, 1));
  return 0;
}

int setColor(lua_State *ls) {
  Object *obj = (Object *)lua_topointer(ls, 1);
  obj->GetMaterial()->color =
      Color((float)lua_tonumber(ls, 2), (float)lua_tonumber(ls, 3),
            (float)lua_tonumber(ls, 4));
  return 0;
}

int setAmbient(lua_State *ls) {
  Object *obj = (Object *)lua_topointer(ls, 1);
  obj->GetMaterial()->ambient = (float)lua_tonumber(ls, 2);
  return 0;
}

int setDiffuse(lua_State *ls) {
  Object *obj = (Object *)lua_topointer(ls, 1);
  obj->GetMaterial()->diffuse = (float)lua_tonumber(ls, 2);
  return 0;
}

int setSpecular(lua_State *ls) {
  Object *obj = (Object *)lua_topointer(ls, 1);
  obj->GetMaterial()->specular = (float)lua_tonumber(ls, 2);
  return 0;
}

int setShininess(lua_State *ls) {
  Object *obj = (Object *)lua_topointer(ls, 1);
  obj->GetMaterial()->shininess = (float)lua_tonumber(ls, 2);
  return 0;
}

int setReflection(lua_State *ls) {
  Object *obj = (Object *)lua_topointer(ls, 1);
  obj->GetMaterial()->reflection = (float)lua_tonumber(ls, 2);
  return 0;
}

int setRefraction(lua_State *ls) {
  Object *obj = (Object *)lua_topointer(ls, 1);
  obj->GetMaterial()->refraction = (float)lua_tonumber(ls, 2);
  return 0;
}

int setOpacity(lua_State *ls) {
  Object *obj = (Object *)lua_topointer(ls, 1);
  obj->GetMaterial()->opacity = (float)lua_tonumber(ls, 2);
  return 0;
}

int setEmissive(lua_State *ls) {
  Object *obj = (Object *)lua_topointer(ls, 1);
  obj->GetMaterial()->emissive = (float)lua_tonumber(ls, 2);
  return 0;
}

int setLight(lua_State *ls) {
  Object *obj = (Object *)lua_topointer(ls, 1);
  obj->SetLight();
  return 0;
}

int cameraPerspective(lua_State *ls) {
  float fovy = (float)lua_tonumber(ls, 1);
  float aspect = (float)lua_tonumber(ls, 2);
  float znear = (float)lua_tonumber(ls, 3);
  float zfar = (float)lua_tonumber(ls, 4);

  Camera::GetInstance()->Perspective(fovy, aspect, znear, zfar);

  return 0;
}

int cameraLookAt(lua_State *ls) {
  Vector3 pos((float)lua_tonumber(ls, 1), (float)lua_tonumber(ls, 2),
              (float)lua_tonumber(ls, 3));
  Vector3 view((float)lua_tonumber(ls, 4), (float)lua_tonumber(ls, 5),
               (float)lua_tonumber(ls, 6));
  Vector3 up((float)lua_tonumber(ls, 7), (float)lua_tonumber(ls, 8),
             (float)lua_tonumber(ls, 9));

  Camera::GetInstance()->LookAt(pos, view, up);

  return 0;
}

int setMaxDepth(lua_State *ls) {
  Raytracer::GetInstance()->SetDepth((int)lua_tonumber(ls, 1));
  return 0;
}

int setMaxDistance(lua_State *ls) {
  Raytracer::GetInstance()->SetMaxDistance((float)lua_tonumber(ls, 1));
  return 0;
}

int setSuperSample(lua_State *ls) {
  Raytracer::GetInstance()->SetSuperSample((int)lua_tonumber(ls, 1));
  return 0;
}

int setFog(lua_State *ls) {
  Raytracer::GetInstance()->SetFog(
      Color((float)lua_tonumber(ls, 1), (float)lua_tonumber(ls, 2),
            (float)lua_tonumber(ls, 3)),
      (float)lua_tonumber(ls, 4), (float)lua_tonumber(ls, 5));
  return 0;
}

int setHDR(lua_State *ls) {
  Raytracer::GetInstance()->SetHDRFilter((int)lua_tonumber(ls, 1),
                                         (float)lua_tonumber(ls, 2),
                                         (float)lua_tonumber(ls, 3));

  return 0;
}

int setHalfToning(lua_State *) {
  Raytracer::GetInstance()->SetHalfToning();
  return 0;
}

int setTexture(lua_State *ls) {
  Object *obj = (Object *)lua_topointer(ls, 1);
  const char *str = lua_tostring(ls, 2);

  if (!strcmp(str, "checker"))
    obj->SetTexture(new CheckerTexture());
  else if (!strcmp(str, "wood"))
    obj->SetTexture(new WoodTexture());
  else if (!strcmp(str, "image"))
    obj->SetTexture(new ImageTexture(lua_tostring(ls, 3)));
  else
    fprintf(stderr, "Unrecognized texture type %s!", str);

  return 0;
}

int setMapping(lua_State *ls) {
  Object *obj = (Object *)lua_topointer(ls, 1);
  const char *str = lua_tostring(ls, 2);

  if (!strcmp(str, "cube"))
    obj->SetMapping(new CubeMapping((float)lua_tonumber(ls, 3),
                                    (float)lua_tonumber(ls, 4),
                                    (float)lua_tonumber(ls, 5)));
  else if (!strcmp(str, "cylinder"))
    obj->SetMapping(new CylinderMapping((float)lua_tonumber(ls, 3),
                                        (float)lua_tonumber(ls, 4)));
  else if (!strcmp(str, "sphere"))
    obj->SetMapping(new SphereMapping((float)lua_tonumber(ls, 3)));
  else
    fprintf(stderr, "Unrecognized mapping %s!", str);

  return 0;
}

// Script class //////////////////////////////////////////////////////////

Script::Script() {
  Raytracer::GetInstance()->Initialize(1024, 1024);

  luaState = luaL_newstate();
  luaL_openlibs(luaState);

  lua_register(luaState, "init", init);
  lua_register(luaState, "clear", clear);
  lua_register(luaState, "render", render);
  lua_register(luaState, "createSphere", createSphere);
  lua_register(luaState, "createPlane", createPlane);
  lua_register(luaState, "setGlobalAmbient", setGlobalAmbient);
  lua_register(luaState, "setColor", setColor);
  lua_register(luaState, "setDiffuse", setDiffuse);
  lua_register(luaState, "setAmbient", setAmbient);
  lua_register(luaState, "setSpecular", setSpecular);
  lua_register(luaState, "setShininess", setShininess);
  lua_register(luaState, "setReflection", setReflection);
  lua_register(luaState, "setRefraction", setRefraction);
  lua_register(luaState, "setOpacity", setOpacity);
  lua_register(luaState, "setEmissive", setEmissive);
  lua_register(luaState, "setLight", setLight);
  lua_register(luaState, "cameraLookAt", cameraLookAt);
  lua_register(luaState, "cameraPerspective", cameraPerspective);
  lua_register(luaState, "setMaxDepth", setMaxDepth);
  lua_register(luaState, "setMaxDistance", setMaxDistance);
  lua_register(luaState, "setSuperSample", setSuperSample);
  lua_register(luaState, "setFog", setFog);
  lua_register(luaState, "setHDR", setHDR);
  lua_register(luaState, "setHalfToning", setHalfToning);
  lua_register(luaState, "setTexture", setTexture);
  lua_register(luaState, "setMapping", setMapping);
}

Script::~Script() { lua_close(luaState); }

bool Script::Run(char *scene) {
  Raytracer *raytracer = Raytracer::GetInstance();
  raytracer->ClearBuffers();
  Scene::GetInstance()->Clear();
  raytracer->ResetSettings();

  int status = luaL_loadfile(luaState, scene);
  if (status) {
    fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(luaState, -1));
    return false;
  }

  status = lua_pcall(luaState, 0, 0, 0);
  if (status) {
    fprintf(stderr, "Failed to evaluate the script: %s\n",
            lua_tostring(luaState, -1));
    return false;
  }
  lua_gc(luaState, LUA_GCCOLLECT, 0);
  return true;
}

}  // namespace vrt
