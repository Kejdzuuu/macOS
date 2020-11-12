#include <stdio.h>
#include <kernel/tty.h>

void kernel_main (void) {
  char os_name[] = "macOS";
  terminal_initialize ();
  printf ("Hello to %x %d %s\n", -112, os_name);
  ascii_art ();
}