#ifndef _GDT_H
#define _GDT_H

#include <stdio.h>
#include <stdint.h>

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

extern struct GDT_entry gdt[GDT_SIZE];

void gdt_setup (void);

#endif