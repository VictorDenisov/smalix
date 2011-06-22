#include <stdarg.h>

#define VIDEO_WIDTH 80    //ширина экрана
#define VIDEO_HEIGHT 25   //высота экрана
#define VIDEO_RAM 0xb8000 //адрес видеопамяти

int tty_cursor;    //положение курсора
int tty_attribute; //текущий аттрибут символа


//Инициализация tty
void init_tty() 
{
    tty_cursor = 0;
    tty_attribute = 7;
}

//Смена текущего аттрибута символа
void textcolor(char c)
{
    tty_attribute = c;
}

//Очистка экрана
void clear()
{
    char *video = (char*)VIDEO_RAM;
    int i;

    for (i = 0; i < VIDEO_HEIGHT*VIDEO_WIDTH; i++) {
        *(video + i*2) = ' ';
    }

    tty_cursor = 0;
}


//Вывод одного символа в режиме телетайпа
void putchar(char c)
{
    char *video = (char*)VIDEO_RAM;
    int i;

    switch (c) {
        case '\n': //Если это символ новой строки
            tty_cursor+=VIDEO_WIDTH;
            tty_cursor-=tty_cursor%VIDEO_WIDTH;
            break;

        default:
            *(video + tty_cursor*2) = c;
            *(video + tty_cursor*2+1) = tty_attribute;
            tty_cursor++;
            break;
    }

    //Если курсор вышел за границу экрана, сдвинем экран вверх на одну строку
    if(tty_cursor>VIDEO_WIDTH*VIDEO_HEIGHT){
        for(i=VIDEO_WIDTH*2;i<=VIDEO_WIDTH*VIDEO_HEIGHT*2+VIDEO_WIDTH*2;i++){
            *(video+i-VIDEO_WIDTH*2)=*(video+i);
        }
        tty_cursor-=VIDEO_WIDTH;
    }
}

//Вывод строки, заканчивающейся нуль-символом
void puts(const char *s)
{
    while(*s) {
        putchar(*s);
        s++;
    }
}

void puthexd(unsigned char digit)
{
    char table[]="0123456789ABCDEF";
    putchar(table[digit]);
}

void putdec(unsigned int byte)
{
    unsigned char b1;
    int b[30];
    signed int nb;
    int i=0;

    while(1){
        b1=byte%10;
        b[i]=b1;
        nb=byte/10;
        if(nb<=0){
            break;
        }
        i++;
        byte=nb;
    }

    for(nb=i+1;nb>0;nb--){
        puthexd(b[nb-1]);
    }
}

void puthex(unsigned char byte)
{
    unsigned  char lb, rb;

    lb=byte >> 4;

    rb=byte & 0x0F;


    puthexd(lb);
    puthexd(rb);
}

void puthexi(unsigned int dword)
{
    puthex( (dword & 0xFF000000) >>24);
    puthex( (dword & 0x00FF0000) >>16);
    puthex( (dword & 0x0000FF00) >>8);
    puthex( (dword & 0x000000FF));
}


void vprintf(const char *fmt, va_list args)
{
    while (*fmt) {

        switch (*fmt) {
            case '%':
                fmt++;

                switch (*fmt) {
                    case 's':
                        puts(va_arg(args, char *));
                        break;

                    case 'c':
                        putchar(va_arg(args, unsigned int));
                        break;

                    case 'i':
                        putdec(va_arg(args, unsigned int));
                        break;

                    case 'x':
                        puthex(va_arg(args, unsigned int));
                        break;

                    case 'X':
                        puthexi(va_arg(args, unsigned int));
                        break;

                    case 'z':
                        textcolor(va_arg(args,unsigned int));
                        break;

                }


                break;

            default:
                putchar(*fmt);
                break;
        }

        fmt++;
    }
}

void printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    textcolor(7);

    vprintf(fmt, args);

    va_end(args);
}
