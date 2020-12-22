#include <kernel/paging.h>

uint32_t page_directory[PAGE_DIRECTORY_SIZE] __attribute__ ((aligned(4096)));
uint32_t page_table[PAGE_TABLE_SIZE] __attribute__ ((aligned(4096)));

extern void load_page_directory (uint32_t *page_dir);
extern void paging_start ();

void paging_setup () {
    for (uint32_t i = 0; i < PAGE_DIRECTORY_SIZE; i++) {
        page_directory[i] = BIT_1;
    }

    for (uint32_t i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i] = ((i * 0x1000)) | BIT_1 | BIT_0;
    }

    page_directory[0] = ((uint32_t)page_table) | BIT_1 | BIT_0;
    page_directory[1] = ((uint32_t)page_table) | BIT_1 | BIT_0;

    load_page_directory (page_directory);
    paging_start ();
}