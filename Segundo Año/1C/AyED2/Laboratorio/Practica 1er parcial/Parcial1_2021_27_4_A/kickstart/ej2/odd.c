#include <stdbool.h>
#include <stdio.h>

#include "odd.h"

bool impar(int x) {
    return x % 2 != 0;
}

bool is_odd_sorted(int array[], unsigned int length) {
    int min = array[1];
    bool res = true;
    for (unsigned int i = 1u; i < length; i++) {
        if (impar(i)) {
            if (min <= array[i]) {
                min = array[i];
            }
            else {
                res = false;
                break;
            }
        }
    }
    return res;
}

int main(void) {
    int arr[] = {5, 1, 8, 2, 3,-1};
    bool res = is_odd_sorted(arr, 6);
    printf("%d\n", res);
}