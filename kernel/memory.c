#include <stdint.h>

#define PAGE_DIRECTORY_POSITION 0x180000

void create_page_table()
{
    printf("Creating page table\n");
    uint32_t* page_directory = (uint32_t*)PAGE_DIRECTORY_POSITION;
    page_directory[0] = PAGE_DIRECTORY_POSITION + 0x1007;
    uint32_t* page_table = (uint32_t*)(PAGE_DIRECTORY_POSITION + 0x1000);
    int i;
    for (i = 0; i < 1024; ++i) {
        page_table[i] = 0x00000007 + i * 0x1000;
    }

    set_page_directory(PAGE_DIRECTORY_POSITION);
}

void set_page_directory(uint32_t* page_directory)
{
    asm("movl %%eax, %%cr3" ::"a"(page_directory));
}

void enable_paging()
{
    asm("movl %cr0, %eax \n orl $0x80000000, %eax \n movl %eax, %cr0");
}
