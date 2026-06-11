/*
** EPITECH PROJECT, 2026
** my_strndup
** File description:
** my_strndup
*/

#include "my.h"

char *my_strndup(const char *s, size_t n)
{
    char *dst = malloc(sizeof(*dst) * (n + 1));
    size_t k = 0;

    if (dst == NULL)
        return NULL;
    for (; k < n; k++) {
        if (s[k] == '\0')
            break;
        dst[k] = s[k];
    }
    dst[k] = '\0';
    return dst;
}
