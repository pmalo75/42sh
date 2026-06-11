/*
** EPITECH PROJECT, 2026
** parse array
** File description:
** parse_array
*/

#include "my.h"

static int starts_with(char *s, char *pattern)
{
    if (!s || !pattern)
        return EXT_ERROR;
    for (int i = 0; pattern[i] != '\0'; i++)
        if (s[i] == '\0' || s[i] != pattern[i])
            return EXT_ERROR;
    return EXT_SUCCESS;
}

char *parse_arr_element(char **arr, char *pattern, int start)
{
    char *element = NULL;

    if (arr == NULL || !arr[0]) {
        return NULL;
    }
    for (int i = 0; arr[i] != NULL; i++) {
        if (starts_with(arr[i], pattern) == EXT_ERROR) {
            continue;
        } else {
            element = my_strdup(arr[i] + start);
            break;
        }
    }
    return element;
}
