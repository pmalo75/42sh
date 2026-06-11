/*
** EPITECH PROJECT, 2026
** str_to_word_array
** File description:
** str_to_word_array
*/

#include "my.h"
#include <stdbool.h>

static int is_sep(char c, char *sep)
{
    for (int i = 0; sep[i] != '\0'; i++) {
        if (c == sep[i])
            return true;
    }
    return false;
}

static int count_elements(const char *s, char *sep)
{
    int count = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (!is_sep(s[i], sep) && (i == 0 || is_sep(s[i - 1], sep)))
            count++;
    }
    return count;
}

static char *fill_element(const char *s, char *sep, int *curr_idx)
{
    int len = 0;
    char *element = NULL;

    for (; s[*curr_idx + len] && !is_sep(s[*curr_idx + len], sep); len++);
    element = my_calloc(len + 1, sizeof(char));
    if (!element)
        return NULL;
    for (int i = 0; i < len; i++) {
        element[i] = s[*curr_idx + i];
    }
    element[len] = '\0';
    *curr_idx += len;
    return element;
}

static void skip_sep(const char *s, char *sep, int *curr_idx)
{
    while (s[*curr_idx] && is_sep(s[*curr_idx], sep))
        (*curr_idx)++;
}

static int build_2d_array(
    int nb_el, char **arr, const char *s, char *sep)
{
    int curr_idx = 0;
    int i = 0;

    for (; i < nb_el; i++) {
        skip_sep(s, sep, &curr_idx);
        arr[i] = fill_element(s, sep, &curr_idx);
        if (!arr[i])
            return EXT_ERROR;
    }
    arr[i] = NULL;
    return EXT_SUCCESS;
}

char **str_to_word_array(const char *s, char *sep)
{
    char **arr = NULL;
    int nb_el = 0;

    if (!s || !sep)
        return NULL;
    nb_el = count_elements(s, sep);
    arr = my_calloc(nb_el + 1, sizeof(char *));
    if (!arr)
        return NULL;
    if (build_2d_array(nb_el, arr, s, sep) == EXT_ERROR) {
        free_arr(arr);
        return NULL;
    } else
        return arr;
}
