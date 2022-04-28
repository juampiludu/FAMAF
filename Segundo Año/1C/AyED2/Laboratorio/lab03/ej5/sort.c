/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    bool res;
    if (x->rank <= y->rank) {
        res = true;
    }
    else {
        res = false;
    }
    return res;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

void swap(player_t a[], int i, int j) {
    player_t tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

static unsigned int partition(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int i, j, pivot;
    pivot = izq;
    i = izq+1;
    j = der;
    while (i <= j)
    {
        if (goes_before(a[i], a[pivot]) /* a[i] <= a[pivot]*/ ) {
            i = i+1;
        }
        else if (goes_before(a[pivot], a[j]) /* a[j] >= a[pivot] */ ) {
            j = j-1;
        }
        else {
            swap(a, i, j);
        }
    }
    swap(a, pivot, j);
    pivot = j;
    return pivot;
}

static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int pivot = partition(a, izq, der);
    if (pivot > izq) {
        quick_sort_rec(a, izq, pivot-1);
    }
    if (pivot < der) {
        quick_sort_rec(a, pivot+1, der);
    }
}

void sort(player_t a[], unsigned int length) {
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u);
}