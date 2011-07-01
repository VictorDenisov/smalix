void kernel_main()
{
    init_tty();
    clear();
    init_interrupts();

    puts("We use C, isn't this great?\n");
    printf("Decimal %i\n"
            "Hexadecimal short: %x\n"
            "Hexadecimal long: %X\n"
            "String: %s\n",
            12345, 0x77, 0x12345678, __DATE__);

    getsn_test();

    for (;;) {
        //putchar('h');
    }
}

void getsn_test()
{
    char buffer[0x100];

    printf("Enter something:");

    getsn(buffer, 0x100);

    printf("You entered: %s\n", buffer);
}
