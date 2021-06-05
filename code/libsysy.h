#pragma once
#include <stdio.h>

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

extern "C" DLLEXPORT int getint() {
  int rv;
  scanf("%d", &rv);
  return rv;
}

extern "C" DLLEXPORT int getch() {
  char rv;
  scanf("%c", &rv);
  return rv;
}

/// putchari - putchar that takes a int and returns 0.
extern "C" DLLEXPORT int putch(int X) {
  fputc((char)X, stderr);
  return 0;
}

extern "C" DLLEXPORT int putint(int i) {
  fprintf(stderr, "%d", i);
  return 0;
}