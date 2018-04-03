/*
 * Singleton.h
 * Decleration of Singleton class
 *
 * Vahid Kazemi
 *********************************************************/

#pragma once

namespace vrt {

template <class T> class Singleton {
public:
  static T *GetInstance() {
    static T instance;
    return &instance;
  }

protected:
  Singleton() {}
};

}  // namespace vrt
