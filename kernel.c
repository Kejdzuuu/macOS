#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Check if you are targeting the wrong os */
#ifdef __linux__
#error "You are not using a cross-compliler, there will be trouble"
#endif

/* This works for the 32-bit ix86 targets */
#ifndef __i386__
#error "This needs to be complied with a ix86-elf compiler"
#endif

/* Text mode color constants */
enum vga_color {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE,
  VGA_COLOR_GREEN,
  VGA_COLOR_CYAN,
  VGA_COLOR_RED,
  VGA_COLOR_MAGENTA,
  VGA_COLOR_BROWN,
  VGA_COLOR_LIGHT_GREY,
  VGA_COLOR_DARK_GREY,
  VGA_COLOR_LIGHT_BLUE,
  VGA_COLOR_LIGHT_GREEN,
  VGA_COLOR_LIGHT_CYAN,
  VGA_COLOR_LIGHT_RED,
  VGA_COLOR_LIGHT_MAGENTA,
  VGA_COLOR_LIGHT_BROWN,
  VGA_COLOR_WHITE
};

static inline uint8_t vga_entry_color (enum vga_color fg, enum vga_color bg) {
  return (bg << 4) | fg;
}

static inline uint16_t vga_entry (unsigned char uc, uint8_t color) {
  return ((uint16_t) color << 8) | (uint16_t) uc;
}

size_t strlen (const char* str) {
  size_t len = 0;
  while (str[len]) {
    len++;
  }
  return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
const char NEWLINE = 10;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

void memcpy (void *destination, const void *source, size_t size) {
  if (!destination || !source) {
    return;
  }

  char *dest = (char *) destination;
  char *src = (char *) source;

  for (size_t i = 0; i < size; i++) {
    dest[i] = src[i];
  }
}

void terminal_initialize () {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_entry_color (VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = (uint16_t *) 0xB8000;

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

void terminal_put_entry_at (char c, uint8_t color, size_t x, size_t y) {
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

  terminal_put_entry_at (c, terminal_color, terminal_column, terminal_row);
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

void kernel_main () {
  /* Initialize terminal interface */
  terminal_initialize ();

  for (size_t i = 0; i < VGA_HEIGHT; i++) {
    char text[] = " Hello World, from kernel!\n";
    text[0] = 'A' + i;
    terminal_write_string (text);
  }
  terminal_write_string ("End");
  ascii_art ();
}
