/*
** EPITECH PROJECT, 2026
** my_putsterr
** File description:
** my_putsterr
*/

#include "my.h"

void my_putsterr(const char *s)
{
    size_t size = my_strlen(s);

    write(2, s, size);
}
