#include <stdio.h>

#ifdef __is_libk
#include <kernel/tty.h>
#endif

int putchar (int n) {
#ifdef __is_libk
  char c = (char) n;
  terminal_write (&c, sizeof (c)); 
#else
  // TODO: implement stdio and write system call
#endif
  return n;
}