#include <string.h>

void * memset (void *ptr, int value, size_t size) {
  if (!ptr) {
    return NULL;
  }

  unsigned char *dest = (unsigned char *) ptr;

  for (size_t i = 0; i < size; i++) {
    dest[i] = (unsigned char) value;
  }
  return ptr;
}