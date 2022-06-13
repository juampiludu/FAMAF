#include <stdio.h>
#include <stdlib.h>

#include "strfuncs.h"

size_t string_length(const char *str) {
    size_t i = 0;
    if (str != NULL) {
        while (str[i] != '\0') {
            i++;
        }
    }
    return i;
}

char *string_filter(const char *str, char c) {
    unsigned int i = 0u;
    size_t j = 0;
    char *new_str = malloc(sizeof(char)*string_length(str));
    while (str[i] != '\0') {
        if (str[i] != c) {
            new_str[j] = str[i];
            j++;
        }
        i++;
    }
    new_str = realloc(new_str, sizeof(char)*string_length(new_str));
    return new_str;
}