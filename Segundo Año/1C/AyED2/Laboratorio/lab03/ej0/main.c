#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

unsigned int data_from_file(const char *path, 
                            unsigned int indexes[], 
                            char letters[], 
                            unsigned int max_size) {

    FILE * file;

    file = fopen(path, "r");
    int idx;
    char lett;
    int count;

    while (fscanf(file, "%d '%c'", &idx, &lett) != EOF && count <= max_size) {
        indexes[count] = idx;
        letters[count] = lett;
        count++;
    }

    fclose(file);

    return count;

}

void sort_letters(unsigned int indexes[], char letters[], char sorted[], unsigned int length) {
    for (unsigned int i = 0u; i < length; i++) {
        sorted[indexes[i]] = letters[i];
    }
}

int main(int argc, char *argv[]) {
    // FILE *file;
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0; 
    
    char *path = argv[1];
    
    length = data_from_file(path, indexes, letters, MAX_SIZE);
    sort_letters(indexes, letters, sorted, length);

    dump(sorted, length);

    return EXIT_SUCCESS;
}

