#include "scancode.h"

#define IRQ_HANDLER(func) void func (void);\
 asm(#func ": pusha \n call _" #func " \n movb $0x20, %al \n outb $0x20 \n popa \n iret \n");\
  void _ ## func(void)


IRQ_HANDLER(irq_timer)
{
    //putchar('x');
}
//Здесь мы храним состояние шифта
char shift = 0;

//IRQ_HANDLER(irq_keyboard)
void irq_keyboard(void)
{
    unsigned char scancode, ascii;
    unsigned char creg;

    //putchar('x');

    //Прочитаем скан-код из порта 0x60
    /*
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

                //Если в результате преобразования нажата клавиша с каким-либо
                //символом, то вывести его на экран
                if(ascii != 0) {
                    putchar(ascii);
                }
            }
            break;
    }

    //Считаем байт состояния клавиатуры
    creg = inportb(0x61);

    //Установим в нем старший бит
    creg |= 1;

    //И запишем обратно
    outportb(0x61, creg);
    */
}


//Ну и наконец - функция, которая установит все обработчики прерываний и разрешит их обработку:

void init_interrupts()
{
    i_install(0x20, &irq_timer, 0x8e);
    i_install(0x21, &irq_keyboard, 0x8e);
    i_setup();
    i_enable();
}

