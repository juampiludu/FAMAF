#include <stdio.h>


struct max_min_result {
    int max_value;
    int min_value;
    unsigned int max_position;
    unsigned int min_position;
};

struct max_min_result compute_max_min(int array[], unsigned int length) {
    unsigned int max_pos, min_pos;
    int min, max;
    max_pos=min_pos=0;
    max=min=array[0];
    struct max_min_result result;
    for (unsigned int i=0; i<length; i++) {
        if (min>array[i]) {
            min_pos = i;
            min = array[i];
        }
        if (max<array[i]) {
            max_pos = i;
            max = array[i];
        }
    }
    result.max_value = max;
    result.min_value = min;
    result.max_position = max_pos;
    result.min_position = min_pos;
    return result;
}

int main(void) {

    int array[] = {0, 9, -1, 4};
    struct max_min_result result = compute_max_min(array, 4);
    printf("%d\n", result.max_value); // Imprime 9
    printf("%d\n", result.min_value); // Imprime -1
    printf("%u\n", result.max_position); // Imprime 1
    printf("%u\n", result.min_position); // Imprime 2

}