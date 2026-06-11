/*
** EPITECH PROJECT, 2026
** vector
** File description:
** vector
*/

#include "my.h"
#include <stdbool.h>
#include <stdlib.h>

bool init_vec(vec_str_t *vec, int init_cap)
{
    vec->cap = init_cap;
    vec->count = 0;
    vec->data = my_calloc(vec->cap, sizeof(char *));
    if (vec->data == NULL) {
        return false;
    }
    return true;
}

bool append_vec(vec_str_t *vec, char *el)
{
    char **tmp = NULL;
    int old_cap = 0;

    if (vec->count >= (vec->cap - 1)) {
        old_cap = vec->cap;
        vec->cap = old_cap * 2;
        tmp = my_realloc_array(vec->data, old_cap, vec->cap);
        if (tmp == NULL) {
            return false;
        }
        vec->data = tmp;
    }
    vec->data[vec->count] = el;
    vec->count++;
    vec->data[vec->count] = NULL;
    return true;
}

void free_vec(vec_str_t *vec)
{
    if (vec->data != NULL) {
        free_arr(vec->data);
        vec->data = NULL;
    }
}
