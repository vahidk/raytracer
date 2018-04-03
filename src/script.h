/*
 * script.h
 * Decleration of Script class
 *
 * Vahid Kazemi
 *********************************************************/

#pragma once

#include "geometry.h"
#include "global.h"
#include "raytracer.h"
#include "singleton.h"
#include "surface.h"


extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}

namespace vrt {

class Script {
public:
  Script();
  ~Script();

  bool Run(char *scene);

private:
  lua_State *luaState;

  void ParallelRender();
};

}  // namespace vrt
