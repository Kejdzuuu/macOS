#include <string.h>

void * memcpy (void *destination, const void *source, size_t size) {
  if (!destination || !source) {
    return NULL;
  }

  char *dest = (char *) destination;
  char *src = (char *) source;

  for (size_t i = 0; i < size; i++) {
    dest[i] = src[i];
  }
  return destination;
}