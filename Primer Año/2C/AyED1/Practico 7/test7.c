#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int main(void) {

    const int N = 4;
    int A[N];
    A[0] = 1;
    A[1] = 30;
    A[2] = 35;
    A[3] = 49;

    unsigned int r = A[0] - A[1];
    int s = max(A[0], A[1]);
    int n = 2;

    while (n != N) {
        r = max(r, (s - A[n]));
        s = max(s, A[n]);
        n = n+1;
    }

    printf("r = %d\n", r);

}