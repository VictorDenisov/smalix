#include <stdint.h>

#define PAGE_DIRECTORY_POSITION 0x180000
#define PAGE_LENGTH 0x1000

void* first_free_page = (void*)PAGE_DIRECTORY_POSITION;

void* allocate_free_page()
{
    void* result = first_free_page;
    first_free_page += 0x1000;
    return result;
}

void set_page_directory(uint32_t* page_directory);

void create_page_directory()
{
    printf("Creating page table\n");

    uint32_t* page_directory = (uint32_t*)allocate_free_page();
    int directory_entry;

    for (directory_entry = 0; directory_entry < 2; ++directory_entry) {

        uint32_t* page_table = (uint32_t*)allocate_free_page();

        page_directory[directory_entry] = (uint32_t)page_table + 0x7;

        int i;
        for (i = 0; i < 1024; ++i) {
            uint32_t value = i * 0x1000 + directory_entry * (0x400000);
            page_table[i] = 0x00000007 + value;
        }
    }

    set_page_directory((uint32_t*)PAGE_DIRECTORY_POSITION);
    printf("Page table is created\n");
}

void set_page_directory(uint32_t* page_directory)
{
    asm("movl %%eax, %%cr3" ::"a"(page_directory));
}

void enable_paging()
{
    asm("movl %cr0, %eax \n orl $0x80000000, %eax \n movl %eax, %cr0");
}
