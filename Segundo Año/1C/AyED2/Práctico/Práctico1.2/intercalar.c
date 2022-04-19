#include <stdio.h>
#include <math.h>

#define LENGTH2N 8

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

void merge(int a[], int lft, int mid, int rgt) {
    int len1 = mid - lft + 1;
    int len2 = rgt - mid;

    int tmp1[len1], tmp2[len2];

    for (int i = 0; i < len1; i++) {
        tmp1[i] = a[lft + i];
    }
    for (int j = 0; j < len2; j++) {
        tmp2[j] = a[mid + 1 + j];
    }

    array_dump(tmp1, len1);
    array_dump(tmp2, len2);

    int i, j, k;
    i = 0;
    j = 0;
    k = lft;

    while (i < len1 && j < len2) {
        if (tmp1[i] <= tmp2[j]) {
            a[k] = tmp1[i];
            i++;
        }
        else {
            a[k] = tmp2[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        a[k] = tmp1[i];
        i++;
        k++;
    }
    
    while (j < len2) {
        a[k] = tmp2[j];
        j++;
        k++;
    }

}


// void merge_sort_rec(int a[], int lft, int rgt) {
//     int mid;
//     if (rgt > lft) {
//         mid = lft + (rgt - lft) / 2;
//         merge_sort_rec(a,lft,mid);
//         merge_sort_rec(a,mid+1,rgt);
//         merge(a,lft,mid,rgt);
//     }
// }

// void merge_sort(int a[], unsigned int length) {
//     merge_sort_rec(a, 0, length);
// }

void intercalar_cada(int a[], unsigned int length, int i) {
    int tam, lft, rgt, mid;

    tam = pow(2, i);

    for (int k = 1; k < length; k++) {
        lft = ((k-1) * tam) + 1;
        rgt = ((k-1) + 1) * tam;
        mid = lft + (rgt - lft) / 2;
        printf("%d, %d\n", lft, rgt);
        merge(a,lft,mid,rgt);
    }
    
    
}

int main(void) {
    int array[8] = {5,2,9,1,6,13,7,-2};
    array_dump(array, LENGTH2N);
    intercalar_cada(array, LENGTH2N, 3);
    array_dump(array, LENGTH2N);
}