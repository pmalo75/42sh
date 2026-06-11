/*
** EPITECH PROJECT, 2025
** write
** File description:
** write
*/

#include "my.h"

char *my_strdup(const char *s)
{
    int i = 0;
    int len = my_strlen(s);
    char *buf = malloc(sizeof(char) * (len + 1));

    if (!buf)
        return NULL;
    for (; s[i] != '\0'; i++) {
        buf[i] = s[i];
    }
    buf[i] = '\0';
    return buf;
}
