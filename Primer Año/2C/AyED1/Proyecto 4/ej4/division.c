#include <stdio.h>
#include <assert.h>
#include "../tools/tools.c"

struct div_t {
    int cociente;
    int resto;
};

struct div_t mDivision;

struct div_t division(int x, int y) {
    mDivision.cociente = x / y;
    mDivision.resto = x % y;
    return mDivision;
}

int main(void) {

    int x = pedirEntero();
    int y = pedirEntero();
    assert(x>=0);
    assert(!(y==0) || y>0);
    division(x, y);
    printf("Cociente: %d\n", mDivision.cociente);
    printf("Resto: %d\n", mDivision.resto);

    return 0;

}