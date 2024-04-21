#ifndef STRINGS_H
#define STRINGS_H

#include <stdio.h>

struct string {
    char* str;
    size_t len;
};

struct string string_lit(char* str_lit);
struct string string_new(char* start, size_t len);
struct string string_readline(FILE* stream);
int string_cmp(const struct string str1, const struct string str2);
int string_cmp_lit(const struct string str1, const char* str2);
void string_write(const struct string string, FILE* stream);
void string_free(struct string* string);
void string_push(struct string* dest, const struct string src);
#define STRING_NPOS -1
size_t string_index_of(const struct string string, char c, size_t start_i);

#endif
