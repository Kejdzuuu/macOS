#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <kernel/tty.h>
#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t * const VGA_MEMORY = (uint16_t *) 0xB8000;

static const char NEWLINE = 10;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t *terminal_buffer;


void terminal_initialize () {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_entry_color (VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = VGA_MEMORY;

  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry (' ', terminal_color);
    }
  }
}

void terminal_scroll () {
  uint16_t *vga_ptr = terminal_buffer;
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    memcpy ((void *) vga_ptr, (void *) (vga_ptr + VGA_WIDTH), VGA_WIDTH);
    vga_ptr += VGA_WIDTH;
  }
}

void terminal_setcolor (uint8_t color) {
  terminal_color = color;
}

void terminal_put_entry_at (unsigned char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = vga_entry (c, color);
}

void terminal_newline () {
  terminal_column = 0;

  if (terminal_row == (VGA_HEIGHT - 1)) {
    terminal_scroll ();
  } else {
    terminal_row++;
  }
}

void terminal_putchar (char c) {
  if (c == NEWLINE) {
    terminal_newline ();
    return;
  }

  terminal_put_entry_at ((unsigned char) c, terminal_color, terminal_column, terminal_row);
  terminal_column++;

  if (terminal_column == VGA_WIDTH) {
    terminal_column = 0;
    
    if (terminal_row == (VGA_HEIGHT - 1)) {
      terminal_scroll ();
    } else {
      terminal_row++;
    }
  }
}

void terminal_write (const char *data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    terminal_putchar (data[i]);
  }
}

void terminal_write_string (const char *data) {
  terminal_write (data, strlen (data));
}

void ascii_art () {
  size_t width = 20, height = 8;
  size_t start_x = 20, start_y = 4;

  for (size_t y = start_y; y < start_y + height; y++) {
    for (size_t x = start_x; x < start_x + width; x++) {
      terminal_put_entry_at (' ', vga_entry_color (VGA_COLOR_BLACK, VGA_COLOR_MAGENTA), x, y);
      terminal_put_entry_at (' ', vga_entry_color (VGA_COLOR_BLACK, VGA_COLOR_CYAN), x + width, y);
      terminal_put_entry_at (' ', vga_entry_color (VGA_COLOR_BLACK, VGA_COLOR_LIGHT_BROWN), x, y + height);
      terminal_put_entry_at (' ', vga_entry_color (VGA_COLOR_BLACK, VGA_COLOR_GREEN), x + width, y + height);
    }
  }
}