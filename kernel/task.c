#include <stdint.h>

uint32_t current_task;

struct task_descriptor
{
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;

    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;

    uint32_t esp;
    uint32_t ebp;

    uint32_t esi;
    uint32_t edi;
};

struct task_descriptor task_list[0x100];

static void store_current_task(struct task_descriptor* d);

void start_init()
{
    store_current_task(&(task_list[0]));
}

static void store_current_task(struct task_descriptor* d)
{
    asm("nop": "=a"(d -> eax));
    asm("nop": "=b"(d -> ebx));
    asm("nop": "=c"(d -> ecx));
    asm("nop": "=d"(d -> edx));

    asm("mov %%esp, %%eax": "=a"(d -> esp));
    asm("mov %%ebp, %%eax": "=a"(d -> ebp));

    asm("mov %%esi, %%eax": "=a"(d -> esi));
    asm("mov %%edi, %%eax": "=a"(d -> edi));

    asm("mov %%cr3, %%eax": "=a"(d -> cr3));
    asm("pop %%eax": "=a"(d -> eip));
    asm("pushfl \n pop %%eax": "=a"(d -> eflags));
}
