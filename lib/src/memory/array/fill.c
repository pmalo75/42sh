/*
** EPITECH PROJECT, 2026
** fill array
** File description:
** fill array
*/

#include "my.h"

static int fill_elements(char **arr, char **buf)
{
    int i = 0;

    for (; arr[i]; i++) {
        buf[i] = my_strdup(arr[i]);
        if (buf[i] == NULL)
            return -1;
    }
    return 0;
}

char **fill_2d_arr(char **arr)
{
    int len = count_2d_arr(arr);
    char **buf = NULL;

    if (len == -1)
        return NULL;
    buf = my_calloc(len + 1, sizeof(char *));
    if (buf == NULL)
        return NULL;
    if (fill_elements(arr, buf) == -1) {
        free_arr(buf);
        return NULL;
    }
    return buf;
}
