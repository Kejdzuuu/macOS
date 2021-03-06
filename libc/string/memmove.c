#include <string.h>

void * memmove (void *destination, const void *source, size_t size) {
  if (!destination || !source) {
    return NULL;
  }

  char *dest = (char *) destination;
  char *src = (char *) source;

  if (dest < src) {
    for (size_t i = 0; i < size; i++) {
      dest[i] = src[i];
    }
  } else {
    for (size_t i = size; i != 0; i--) {
      dest[i-1] = src[i-1];
    }
  }
  return dest;
}