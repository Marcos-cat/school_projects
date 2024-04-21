#include "strings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string string;

string string_lit(char* str_lit) {
    size_t len = strlen(str_lit);
    char* str = malloc(len);
    memcpy(str, str_lit, len);
    return (string){.str = str, .len = len};
}

string string_new(char* start, size_t len) {
    char* str = malloc(len);
    memcpy(str, start, len);
    return (string){.str = str, .len = len};
}

string string_readline(FILE* stream) {
    char line[1024];
    if (NULL == fgets(line, sizeof(line), stream)) {
        return (string){.str = NULL};
    }
    line[sizeof(line) - 1] = 0;

    for (size_t i = 0; i < sizeof(line); i++) {
        if ('\n' == line[i] || 0 == line[i]) {
            line[i] = 0;
            break;
        }
    }

    return string_lit(line);
}

int string_cmp(const string str1, const string str2) {
    size_t min = str2.len > str1.len ? str1.len : str2.len;
    size_t cmp = strncmp(str1.str, str2.str, min);
    if (0 == cmp) return str1.len - str2.len;
    return cmp;
}

int string_cmp_lit(const string str1, const char* str2) {
    size_t str2_len = strlen(str2);
    size_t min = str2_len > str1.len ? str1.len : str2_len;
    size_t cmp = strncmp(str1.str, str2, min);
    if (0 == cmp) return str1.len - str2_len;
    return cmp;
}

void string_write(const string string, FILE* stream) {
    fwrite(string.str, sizeof(char), string.len, stream);
}

void string_free(string* string) {
    free(string->str);
    string->str = NULL;
    string->len = 0;
}

void string_push(string* dest, const string src) {
    dest->str = realloc(dest->str, dest->len + src.len);
    memcpy(dest->str + dest->len, src.str, src.len);
    dest->len += src.len;
}

size_t string_index_of(const string string, char c, size_t start_i) {
    for (size_t i = start_i; i < string.len; i++) {
        if (string.str[i] == c) return i;
    }
    return -1;
}
