/*
** EPITECH PROJECT, 2025
** write
** File description:
** write
*/

#include "my.h"

char *my_strcpy(char *dst, const char *src)
{
    int i = 0;

    if (!dst || !src)
        return NULL;
    for (; src[i] != '\0'; i++) {
        dst[i] = src[i];
    }
    dst[i] = '\0';
    return dst;
}
