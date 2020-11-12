#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define STRING_LEN 36

static bool print (const char *data, size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (putchar (data[i]) == EOF) {
      return false;
    }
  }
  return true;
}

void reverse_str (char *str, size_t len) {
  char *ptr;

  if (len <= 1) {
    return;
  }

  ptr = &str[len-1];

  for (size_t i = 0; i < len/2; i++) {
    char c = *str;
    *str = *ptr;
    *ptr = c;
    str++;
    ptr--;
  }
}

char * itoa (int number, char *buffer, int base) {
  char digits[] = "0123456789ABCDEF";
  bool is_negative = false;
  char *ptr = buffer;
  size_t len;

  if (base > 16) {
    return NULL;
  }

  if (number < 0) {
    is_negative = true;
    number = -number;
  }

  do {
    *ptr = digits[number % base];
    number /= base;
    ptr++;
  } while (number);

  if (is_negative) {
    *ptr = '-';
    ptr++;
  }

  *ptr = '\0';
  len = strlen (buffer);
  reverse_str (buffer, len);

  return buffer;
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
    } else if (format[0] == 'd') {
      format++;
      int num = va_arg (parameters, int);
      char str[STRING_LEN];
      itoa (num, str, 10);
      size_t len = strlen (str);
      /*size_t len = get_num_of_digits (num);
      if (num < 0) {
        len++;
      } */
      if (max_chars_remaining < len) {
        // Char counter overflow
        // TODO: Set errno to EOVERFLOW
        return -1;
      }
      if (!print (str, len)) {
        return -1;
      }
      //print_num ((int)len);
      chars_written += len;
    } else {
      size_t len = 1;
      while (format[0] && format[0] != '%') {
        len++;
        format++;
      }
      format = format_begin;
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