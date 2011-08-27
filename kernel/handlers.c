#include "scancode.h"

#define IRQ_HANDLER(func) void func (void);\
 asm(#func ": pusha \n call _" #func " \n movb $0x20, %al \n outb $0x20 \n popa \n iret \n");\
  void _ ## func(void)
  
#define IRQ_ERROR_HANDLER(func) void func (void);\
 asm(#func ": pusha \n call _" #func " \n movb $0x20, %al \n outb $0x20 \n popa \n inc %esp \n inc %esp \n iretl \n");\
  void _ ## func(void)

IRQ_HANDLER(irq_timer)
{
}

IRQ_HANDLER(irq_dumb)
{
    puts("e\n");
    asm("hlt");
}

IRQ_HANDLER(irq_dumb0)
{
    puts("e0\n");
    asm("hlt");
}

IRQ_HANDLER(irq_dumb1)
{
    puts("e1\n");
    asm("hlt");
}

IRQ_HANDLER(irq_dumb2)
{
    puts("e2\n");
    asm("hlt");
}

IRQ_HANDLER(irq_dumb3)
{
    puts("e3\n");
    asm("hlt");
}

IRQ_HANDLER(irq_dumb4)
{
    puts("e4\n");
    asm("hlt");
}

IRQ_HANDLER(irq_dumb5)
{
    puts("e5\n");
    asm("hlt");
}

IRQ_HANDLER(irq_dumb6)
{
    puts("e6\n");
    asm("hlt");
}

IRQ_HANDLER(irq_dumb7)
{
    puts("e7\n");
    asm("hlt");
}

IRQ_ERROR_HANDLER(irq_dumb_error)
{
    puts("e\n");
}

IRQ_ERROR_HANDLER(irq_dumb_error8)
{
    puts("e8\n");
    asm("hlt");
}

IRQ_ERROR_HANDLER(irq_dumb_error9)
{
    puts("e9\n");
    asm("hlt");
}

IRQ_ERROR_HANDLER(irq_dumb_error10)
{
    puts("e10\n");
    asm("hlt");
}

IRQ_ERROR_HANDLER(irq_dumb_error11)
{
    puts("e11\n");
    asm("hlt");
}

IRQ_ERROR_HANDLER(irq_dumb_error12)
{
    puts("e12\n");
    asm("hlt");
}

IRQ_ERROR_HANDLER(irq_dumb_error13)
{
    puts("e13\n");
    asm("hlt");
}

IRQ_ERROR_HANDLER(irq_dumb_error14)
{
    puts("e14\n");
    asm("hlt");
}

IRQ_HANDLER(irq_dumb16)
{
    puts("e16\n");
    asm("hlt");
}

IRQ_ERROR_HANDLER(irq_dumb_error17)
{
    puts("e17\n");
    asm("hlt");
}

IRQ_HANDLER(irq_keyboard)
{
    static unsigned char shift = 0;
    unsigned char scancode, ascii;
    unsigned char creg;

    //Прочитаем скан-код из порта 0x60
    scancode = inportb(0x60);

    switch(scancode) {

        //Скан-коды нажатого шифта
        case 0x36: 
        case 0x2A:
            shift = 1;
            break;

            //Скан-коды отпущенного шифта
        case 0x36 + 0x80:
        case 0x2A + 0x80:
            shift = 0;
            break;

        default:
            //Если клавиша отпущена...
            if(scancode >= 0x80) {
                //То ничего не делать      

            } else {
                //А если нажата...

                if(shift){
                    //Если шифт нажат, но преобразовать скан-код в "шифтнутое" ASCII
                    ascii = scancodes_shifted[scancode];

                } else {
                    //А если не нажат - то в обычное
                    ascii = scancodes[scancode];
                }

                //If ascii character put it to the buffer.
                if(ascii != 0) {
                    ungetc(ascii);
                }
            }
            break;
    }

    //Считаем байт состояния клавиатуры
    creg = inportb(0x61);

    //Установим в нем старший бит
    creg |= 0x80;

    //И запишем обратно
    outportb(0x61, creg);
}

//Setup handlers. Enable irq processing.

void init_interrupts()
{
    i_install(0, &irq_dumb0, 0x8f);
    i_install(1, &irq_dumb1, 0x8f);
    i_install(2, &irq_dumb2, 0x8e);
    i_install(3, &irq_dumb3, 0x8e);
    i_install(4, &irq_dumb4, 0x8e);
    i_install(5, &irq_dumb5, 0x8f);
    i_install(6, &irq_dumb6, 0x8f);
    i_install(7, &irq_dumb7, 0x8f);

    i_install(8, &irq_dumb_error8, 0x8f);
    i_install(9, &irq_dumb_error9, 0x8f);
    i_install(10, &irq_dumb_error10, 0x8f);
    i_install(11, &irq_dumb_error11, 0x8f);
    i_install(12, &irq_dumb_error12, 0x8f);
    i_install(13, &irq_dumb_error13, 0x8f);
    i_install(14, &irq_dumb_error14, 0x8f);

    i_install(16, &irq_dumb16, 0x8f);
    i_install(17, &irq_dumb_error17, 0x8f);

    int i;
    for (i = 17; i < 32; ++i) {
        i_install(i, &irq_dumb_error, 0x8f);
    }

    i_install(0x20, &irq_timer, 0x8e);
    i_install(0x21, &irq_keyboard, 0x8e);

    for (i = 0x22; i < 0x70; ++i) {
        i_install(i, &irq_dumb, 0x8e);
    }

    i_setup();
    i_enable();
}

