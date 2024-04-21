#include <stdlib.h>

struct vector {
    void* items;
    size_t el_size;
    size_t len;
    size_t cap;
};

struct vector vector_new(size_t el_size);
void vector_push(struct vector* vec, const void* el);
void* vector_at(const struct vector* vec, size_t i);
void vector_del(struct vector* vec, size_t i);
void vector_sort(struct vector* vec, int cmp(const void*, const void*));
