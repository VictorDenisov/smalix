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
    char *video = VIDEO_RAM;
    int i;

    for (i = 0; i < VIDEO_HEIGHT*VIDEO_WIDTH; i++) {
        *(video + i*2) = ' ';
    }

    tty_cursor = 0;
}


//Вывод одного символа в режиме телетайпа
void putchar(char c)
{
    char *video = VIDEO_RAM;
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

