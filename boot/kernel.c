void kernel_main()
{
    init_tty();
    clear();
    init_interrupts();

    puts("We use C, isn't this great?\n");
    puts("Hello all\n");
    printf("Dec %x", 10);
    int i;
    for (i = 0; i < 10; ++i)
        putchar('h');

    for(;;);
}
