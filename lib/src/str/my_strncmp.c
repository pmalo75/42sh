/*
** EPITECH PROJECT, 2026
** my_strncmp
** File description:
** my_strncmp
*/

#include "my.h"

int my_strncmp(const char *s1, const char *s2, size_t n)
{
    for (size_t k = 0; k < n; k++) {
        if (s1[k] == '\0' || s2[k] == '\0')
            return (unsigned char)s1[k] - (unsigned char)s2[k];
        if (s1[k] != s2[k])
            return (unsigned char)s1[k] - (unsigned char)s2[k];
    }
    return 0;
}
