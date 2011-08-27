#include <stdint.h>

uint32_t current_task_id;

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

#define restore_task(d) \
    asm("nop":: "a"((d) -> eax)); \
    asm("nop":: "b"((d) -> ebx)); \
    asm("nop":: "c"((d) -> ecx)); \
    asm("nop":: "d"((d) -> edx)); \
    asm("mov %%eax, %%esp":: "a"(d -> esp)); \
    asm("mov %%eax, %%ebp":: "a"(d -> ebp)); \
    asm("mov %%eax, %%esi":: "a"(d -> esi)); \
    asm("mov %%eax, %%edi":: "a"(d -> edi)); \
    asm("mov %%eax, %%cr3":: "a"(d -> cr3)); \
    asm("push %%eax \n popfl":: "a"(d -> eflags)); \
    asm("jmp %0":: "a"(d -> eip));

#define store_current_task(d) \
    asm("nop": "=a"((d) -> eax)); \
    asm("nop": "=b"((d) -> ebx)); \
    asm("nop": "=c"((d) -> ecx)); \
    asm("nop": "=d"((d) -> edx)); \
    asm("mov %%esp, %%eax": "=a"((d) -> esp)); \
    asm("mov %%ebp, %%eax": "=a"((d) -> ebp)); \
    asm("mov %%esi, %%eax": "=a"((d) -> esi)); \
    asm("mov %%edi, %%eax": "=a"((d) -> edi)); \
    asm("mov %%cr3, %%eax": "=a"((d) -> cr3)); \
    asm("pop %%eax": "=a"((d) -> eip)); \
    asm("push %eax"); \
    asm("pushfl \n pop %%eax": "=a"((d) -> eflags));

static uint32_t create_new_task();

void init();

void schedule(uint32_t task_id);

void start_init()
{
    current_task_id = create_new_task();

    store_current_task((&task_list[current_task_id]));
    task_list[current_task_id].eip = (uint32_t)init;
    printf("%X \n", init);
    restore_task((&(task_list[current_task_id])));
}

void reschedule()
{
    store_current_task(&(task_list[current_task_id]));
}

static uint32_t create_new_task()
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

    task_list[max_task_id].eip = 0;
    task_list[max_task_id].eflags = 0;

    uint32_t result = max_task_id;
    ++max_task_id;
    return result;
}

int fork()
{
    int new_task_id = create_new_task();
    //store_current_task(&task_list[new_task_id]);
}

void init()
{
    for (;;) {
        printf("init");
    }
}

