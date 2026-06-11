/*
** EPITECH PROJECT, 2026
** my_tokenizer
** File description:
** my_tokenizer
*/

#include "my.h"
#include <stdlib.h>
#include <stdbool.h>

static char *copy_element(
    const char *s, bool *ign, bool *stp, size_t *idx)
{
    size_t start = 0;
    size_t len = 0;
    char *el = NULL;

    start = *idx;
    while (s[*idx] != '\0' && ign[(unsigned char)s[*idx]] == false
        && stp[(unsigned char)s[*idx]] == false)
        (*idx)++;
    len = *idx - start;
    el = malloc(sizeof(char) * (len + 1));
    if (el == NULL) {
        return NULL;
    }
    for (int i = 0; i < len; i++) {
        el[i] = s[start + i];
    }
    el[len] = '\0';
    return el;
}

static bool safe_append(vec_str_t *vec, char *el)
{
    if (el == NULL) {
        return false;
    }
    if (append_vec(vec, el) == false) {
        free(el);
        return false;
    }
    return true;
}

static char **finalize_vec(vec_str_t *vec)
{
    char **tmp = NULL;

    if (vec->count == 0) {
        free_vec(vec);
        return NULL;
    }
    tmp = my_realloc_array(vec->data, vec->cap, (vec->count + 1));
    if (tmp == NULL) {
        free_vec(vec);
        return NULL;
    }
    return tmp;
}

static char **build_token(
    const char *s, bool *ign, bool *stp, size_t *idx)
{
    vec_str_t vec;

    if (init_vec(&vec, 2) == false) {
        return NULL;
    }
    while (s[*idx] != '\0') {
        while (s[*idx] != '\0' && ign[(unsigned char)s[*idx]] == true)
            (*idx)++;
        if (s[*idx] == '\0' || stp[(unsigned char)s[*idx]] == true)
            break;
        if (safe_append(&vec, copy_element(s, ign, stp, idx)) == false) {
            free_vec(&vec);
            return NULL;
        }
    }
    return finalize_vec(&vec);
}

char **my_tokenizer(
    const char *s, char *ignore, char *stop, size_t *idx)
{
    bool ign[ASCII] = {false};
    bool stp[ASCII] = {false};

    if (s == NULL
        || ignore == NULL || stop == NULL) {
        return NULL;
    }
    for (size_t i = 0; ignore[i] != '\0'; i++)
        ign[(unsigned char)ignore[i]] = true;
    for (size_t i = 0; stop[i] != '\0'; i++)
        stp[(unsigned char)stop[i]] = true;
    return build_token(s, ign, stp, idx);
}
