#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int a=-1,b=-1,c=-1;
    printf("Buenas tardes. Digame dos numeros: ");
    scanf("%d %d", &a, &b);
    c = a + b;
    printf("\n%d+%d=%d", a,b,c);
    return 0;
}
