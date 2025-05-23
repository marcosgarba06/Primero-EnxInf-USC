#include <stdio.h>

float distancia(int planeta) {
    if (planeta == 1)
        return (4 + 1) / 10.0;
    else if (planeta == 2)
        return (4 + 3) / 10.0;
    else if (planeta == 3)
        return (4 + 6) / 10.0;
    else
        return (4 + 2 * (10 * distancia(planeta - 1) - 4)) / 10.0;
}

int main(int argc, char const *argv[])
{
    int planeta;
    planeta = 4;
    distancia(planeta);
    printf("La distancia del planeta %d es: %.2f\n", planeta, distancia(planeta));
    return 0;
}
