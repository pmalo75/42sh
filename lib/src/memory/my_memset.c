/*
** EPITECH PROJECT, 2026
** my_memset
** File description:
** my_memset
*/

#include "my.h"

void *my_memset(void *s, int c, size_t n)
{
    unsigned char *ptr = (unsigned char *)s;

    while (n) {
        *ptr = (unsigned char)c;
        ptr++;
        n--;
    }
    return s;
}
