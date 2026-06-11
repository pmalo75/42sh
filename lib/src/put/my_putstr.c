/*
** EPITECH PROJECT, 2025
** putstr
** File description:
** putstr
*/

#include "my.h"

void my_putstr(const char *s)
{
    size_t size = my_strlen(s);

    write(1, s, size);
}
