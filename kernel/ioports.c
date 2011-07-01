/*
   ioports.c - функции работы с портами ввода/вывода
 */

__inline__ void outportb(unsigned short port, unsigned char value)
{
    asm("outb %b0,%w1":: "a"(value), "d"(port));
}

__inline__ char inportb(unsigned short port)
{
    char value;

    asm("inb %w1, %b0": "=a"(value): "d"(port));

    return value;
}

