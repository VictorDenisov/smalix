#include <stdint.h>

void create_page_table()
{
    printf("Creating page table\n");
    int* page_directory = (int*)0x180000;
    page_directory[0] = 0x181007;
    int* page_table = (int*)0x181000;
    int i;
    for (i = 0; i < 1024; ++i) {
        page_table[i] = 0x00000007 + i * 0x1000;
    }

    set_page_directory(0x00180000);
}

void set_page_directory(uint32_t* page_directory)
{
    asm("movl %%eax, %%cr3" ::"a"(page_directory));
}

void enable_paging()
{
    printf("Enabling paging\n");
    asm("movl %cr0, %eax \n orl $0x80000000, %eax \n movl %eax, %cr0");
}
