#include <stdint.h>
#include <kernel/gdt.h>
#include <stdio.h>

#define GDT_SIZE 3

struct GDT_entry {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;
} __attribute__ ((packed));

struct GDT_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__ ((packed));

struct GDT_entry gdt[GDT_SIZE];
struct GDT_ptr gdt_ptr;

// Function in start.asm
extern void gdt_flush ();

// Setting up GDT entry
void gdt_add_entry (uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
  // GDT entry base address
  gdt[num].base_low = (base & 0xFFFF);
  gdt[num].base_middle = (base >> 16) & 0xFF;
  gdt[num].base_high = (base >> 24) & 0xFF;

  // GDT entry limit
  gdt[num].limit_low = (limit & 0xFFFF);
  gdt[num].granularity = (limit >> 16) & 0xF;

  // GDDT entry granularity and access flags
  gdt[num].granularity |= (granularity & 0xF0);
  gdt[num].access = access;
}

void gdt_setup () {
  // set GDT pointer and limit
  gdt_ptr.base = (uint32_t) &gdt;
  gdt_ptr.limit = (sizeof (struct GDT_entry) * GDT_SIZE) - 1;

  // NULL descriptor
  gdt_add_entry (0, 0, 0, 0, 0);

  // Code Segment
  gdt_add_entry (1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

  // Data Segment
  gdt_add_entry (2, 0, 0xFFFFFFFF, 0x92, 0xCF);


  // Flush the old GDT and install a new one
  gdt_flush ();
}
