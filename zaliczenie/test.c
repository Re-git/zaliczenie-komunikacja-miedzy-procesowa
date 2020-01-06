#include <stdio.h>

struct s
    {
        int value;
        int* ptr;
    } struktura;

int main()
{
    struktura.value = 5;
    struct s* wskaznik = &struktura;
    struct s** wskaznik2 = &wskaznik;
    struct s* wskaznik3 = *wskaznik2;
    printf("%d\n", struktura.value);
    printf("%p\n", wskaznik);
    printf("%p\n", wskaznik3);
    *wskaznik2 = 0x0000000000;
    printf("%p\n", wskaznik);
    printf("%p\n", wskaznik3);
}