#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../tools/tools.c"

int nesimo_primo(int N) {
    int cont_primos = 0;
    int tot;
    for (int i = 0; cont_primos < N; i++) {
        if (primo(i)) {
            cont_primos++;
            tot = i;
        }
    }
    return tot;
}

int main(void) {
    bool valid = true;
    while (valid)
    {
        int N = input("Primo numero: ");
        if (N<0)
        {
            printf("Solamente se deben ingresar numeros positivos.\n");
        }
        else
        {
            printf("El primo numero %d es: %d\n", N, nesimo_primo(N));
            printf("Primeros primos: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59...\n");
            valid = false;
        }
    }
}