#include "vector.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector vector;

const size_t INIT_LEN = 4;

vector vector_new(size_t el_size) {
    void* items = malloc(el_size * INIT_LEN);
    return (vector){
        .items = items,
        .el_size = el_size,
        .len = 0,
        .cap = INIT_LEN,
    };
}

void vector_push(vector* vec, const void* restrict el) {
    if (vec->cap < vec->len + 1) {
        vec->cap *= 2;
        vec->items = realloc(vec->items, vec->cap * vec->el_size);
    }

    memcpy(vec->items + (vec->len * vec->el_size), el, vec->el_size);
    vec->len++;
}

void* vector_at(const vector* vec, size_t i) {
    if (i >= vec->len) return NULL;
    return vec->items + (i * vec->el_size);
}

void vector_del(vector* vec, size_t i) {
    if (i >= vec->len) return;
    if (i == vec->len - 1) {
        vec->len--;
        return;
    }

    void* deleted_ptr = vector_at(vec, i);
    size_t moved_items = vec->len - i - 1;
    memmove(
        deleted_ptr, deleted_ptr + vec->el_size, moved_items * vec->el_size
    );

    vec->len--;
}

void vector_sort(vector* vec, int cmp(const void*, const void*)) {
    qsort(vec->items, vec->len, vec->el_size, cmp);
    // for (size_t i = 0; i < vec->len; i++) {
    //     bool swapped = false;
    //     for (size_t j = 0; j < vec->len - i - 1; j++) {
    //         if (cmp(vector_at(vec, j), vector_at(vec, j + 1)) < 0) {
    //             swapped = true;
    //
    //             void* el1 = vector_at(vec, j);
    //             void* el2 = vector_at(vec, j + 1);
    //
    //             void* tmp = malloc(vec->el_size);
    //             memcpy(tmp, el1, vec->el_size);
    //             memcpy(el1, el2, vec->el_size);
    //             memcpy(el2, tmp, vec->el_size);
    //             free(tmp);
    //         }
    //     }
    //     if (!swapped) break;
    // }
}
