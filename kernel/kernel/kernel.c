#include <stdio.h>
#include <kernel/tty.h>

void kernel_main (void) {
  char os_name[] = "macOS";
  terminal_initialize ();
  printf ("Hello to %s\n");
}