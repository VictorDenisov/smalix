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

uint32_t max_task_id = 0;

static void store_current_task(struct task_descriptor* d);

static void create_new_task();

void start_init()
{
    store_current_task(&(task_list[0]));
    create_new_task();
}

static void create_new_task()
{
    //TODO this function should be finished
    task_list[max_task_id].cr3 = 0;
    task_list[max_task_id].eax = 0;
    task_list[max_task_id].ebx = 0;
    task_list[max_task_id].ecx = 0;
    task_list[max_task_id].edx = 0;

    task_list[max_task_id].esp = 0;
    task_list[max_task_id].ebp = 0;

    task_list[max_task_id].esi = 0;
    task_list[max_task_id].edi = 0;

    ++max_task_id;
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
