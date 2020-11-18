#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>


void kernel_main (void) {
  char os_name[] = "macOS";
  terminal_initialize ();
  printf ("Welcome to %s\n", os_name);
  printf ("GDT:\n");
  ascii_art ();
  gdt_setup();
}