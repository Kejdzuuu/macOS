#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static bool print (const char *data, size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (putchar (data[i]) == EOF) {
      return false;
    }
  }
  return true;
}

int printf (const char *format, ...) {
  va_list parameters;
  va_start (parameters, format);

  int chars_written = 0;

  while (*format != '\0') {
    size_t max_chars_remaining = INT_MAX - chars_written;

    if (format[0] != '%' || format[1] == '%') {
      if (format[0] == '%') {
        // Escaped '%', skip over first
        format++;
      }
      size_t amount = 1;
      while (format[amount] && format[amount] != '%') {
        // Count chars until null terminator or '%'
        amount++;
      }
      if (max_chars_remaining < amount) {
        // Char counter overflow
        // TODO: Set errno to EOVERFLOW
        return -1;
      }
      if (!print (format, amount)) {
        return -1;
      }
      format += amount;
      chars_written += amount;
      continue;
    }

    const char *format_begin = format;
    format++;

    if (format[0] == 'c') {
      format++;
      char c = (char) va_arg (parameters, int);
      if (max_chars_remaining == 0) {
        // Char counter overflow
        // TODO: Set errno to EOVERFLOW
        return -1;
      }
      if (!print (&c, sizeof (c))) {
        return -1;
      }
      chars_written++;
    } else if (format[0] == 's') {
      format++;
      const char *str = va_arg (parameters, const char *);
      size_t len = strlen (str);
      if (max_chars_remaining < len) {
        // Char counter overflow
        // TODO: Set errno to EOVERFLOW
        return -1;
      }
      if (!print (str, len)) {
        return -1;
      }
      chars_written += len;
    } else {
      format = format_begin;
      size_t len = strlen (format);
      if (max_chars_remaining < len) {
        // Char counter overflow
        // TODO: Set errno to EOVERFLOW
        return -1;
      }
      if (!print (format, len)) {
        return -1;
      }
      chars_written += len;
      format += len;
    }
  }
  va_end (parameters);
  return chars_written;
}