#ifndef _PAGING_H
#define _PAGING_H

#include <stdint.h>

#define PAGE_DIRECTORY_SIZE 0x400
#define PAGE_TABLE_SIZE 0x400

#define BASE_ADDR 0x1000
#define BIT_0 0x1
#define BIT_1 (0x1 << 1)
#define BIT_2 (0x1 << 2)
#define BIT_5 (0x1 << 5)
#define BIT_7 (0x1 << 6)


void paging_setup (void);

#endif