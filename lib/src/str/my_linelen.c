/*
** EPITECH PROJECT, 2026
** my line len
** File description:
** my line len
*/

#include "my.h"

size_t my_linelen(const char *line)
{
    size_t len = 0;

    for (; line[len] != '\n' && line[len] != '\0'; len++);
    return len;
}
