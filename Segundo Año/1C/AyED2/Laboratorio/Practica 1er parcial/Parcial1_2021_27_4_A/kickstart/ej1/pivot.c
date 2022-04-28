#include <stdbool.h>
#include <stdio.h>

#include "pivot.h"

bool is_pivot(int array[], unsigned int length, unsigned int piv) {
    bool res = true; 
    unsigned int j, k;

    for (j=0u; j < piv; j++) {
        if (array[j] > array[piv]) {
            res = false;
            piv=length;
            break;
        }
    }

    for (k=length-1u; piv < k; k--) {
        if (array[piv] >= array[k]) {
            res = false;
            break;
        }
    }

    return res;
}

int main(void) {
    int arr[] = {1,1,1,5};
    bool res = is_pivot(arr, 4, 1);
    printf("%d\n", res);
}