#include "array_helpers.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>


unsigned int array_from_file(int array[],
           unsigned int max_size,
           const char *filepath) {
    
    FILE * file;
    unsigned int res;
    int numIn;
    unsigned int counter;

    file = fopen(filepath, "r");
    counter = 0u;

    while (fscanf(file, "%d", &numIn) == 1) {
        if (counter == 0) {
            res = numIn;
            assert(res <= max_size);
        }
        else {
            array[counter-1] = numIn;
        }
        ++counter;
    }

    fclose(file);

    return res;

}

void array_dump(int a[], unsigned int length) {
    printf("[");
    for (unsigned int i = 0u; i < length; ++i) {
        if (i == length-1) {
            printf("%d", a[i]);
        }
        else {
            printf("%d, ", a[i]);
        }
    }
    printf("]\n");
}

bool array_is_sorted(int a[], unsigned int length) {
    bool res;
    res = true;
    for (unsigned int i = 0u; i < length-1; ++i) {
        if (a[i] > a[i+1]) {
            res = false;
            break;
        }
    }
    return res;
}

void array_swap(int a[], unsigned int i, unsigned int j) {
    int tmp;
    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void array_inverter(int a[], unsigned int length) {
    for (unsigned int i = 0u; i < length-1-i; ++i) {
        array_swap(a, i, length-1-i);
    }
}