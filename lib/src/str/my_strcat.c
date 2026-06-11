/*
** EPITECH PROJECT, 2025
** strcat
** File description:
** strcat
*/

#include "my.h"

char *my_strcat(char *dst, const char *src)
{
    int i = 0;
    int dst_len = 0;

    if (!dst || !src)
        return NULL;
    dst_len = my_strlen(dst);
    while (src[i] != '\0') {
        dst[dst_len + i] = src[i];
        i++;
    }
    dst[dst_len + i] = '\0';
    return (dst);
}
