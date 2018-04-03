#include "script.h"

int main(int argc, char **argv) {
  fprintf(stderr, "****************************\n");
  fprintf(stderr, "* V.R.T. Engine\n");
  fprintf(stderr, "* by Vahid Kazemi\n");
  fprintf(stderr, "****************************\n");

  if (argc != 2) {
    printf("Usage: raytracer scripts/basic.lua\n");
    return 0;
  }

  vrt::Script().Run(argv[1]);
  return 0;
}
