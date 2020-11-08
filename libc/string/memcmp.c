#include <string.h>

int memcmp (const void *ptr_a, const void *ptr_b, size_t size) {
  const unsigned char *a = (const unsigned char *) ptr_a;
  const unsigned char *b = (const unsigned char *) ptr_b;

  for (size_t i = 0; i < size; i++) {
    if (a[i] < b[i]) {
      return -1;
    } else if (a[i] > b[i]) {
      return 1;
    }
  }
  return 0;
}