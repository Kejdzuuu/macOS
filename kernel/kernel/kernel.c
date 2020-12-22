#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/paging.h>

void kernel_main (void) {
  char os_name[] = "macOS";
  
  terminal_initialize ();
  printf ("Welcome to %s\n", os_name);
  printf ("Enabling GDT\n");
  //ascii_art ();
  gdt_setup();
  paging_setup();
  
  // zerowy wpis w PD
  uint32_t *num = (uint32_t *)0x3440;
  *num = 4;
  printf ("%x\n", *num);

  // pierwszy wpis w PD
  uint32_t *num2 = (uint32_t *)0x403440;
  printf ("%x\n", *num2);
  *num2 = 5;
  printf ("%x\n", *num);

}