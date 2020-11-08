#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__))
void abort (void) {
#ifdef __is_libk
  // TODO: proper kernel panic
  printf ("kernel panic: abort\n");
#else
  // TODO: terminate the process
  printf ("abort\n");
#endif
  while (1);
  __builtin_unreachable();
}