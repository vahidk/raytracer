/*
 * Engine.h
 * Decleration of Engine class
 *
 * Vahid Kazemi
 *********************************************************/

#pragma once

#include <algorithm>
#include <iostream>
#include <math.h>
#include <thread>
#include <vector>

namespace vrt {

template <class F, class T>
void ParallelFor(T start, T end, F f, uint32_t num_threads = 0) {
  if (num_threads == 0) {
    num_threads = std::thread::hardware_concurrency();
  }
  const T len = end - start;
  if (num_threads > len) {
    num_threads = len;
  }
  const T stride = (T)ceil(float(len) / float(num_threads));
  std::vector<std::thread> threads;

  for (T i = start; i < end; i += stride) {
    T max_i = std::min(i + stride, end);
    threads.emplace_back([=]() {
      for (T j = i; j < max_i; ++j) {
        f(j);
      }
    });
  }
  for (auto &thread : threads) {
    thread.join();
  }
}

}  // namespace vrt
