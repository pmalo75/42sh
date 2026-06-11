/*
** EPITECH PROJECT, 2026
** is_number
** File description:
** is_number
*/

#include "my.h"
int is_number(const char *s)
{
    if (s == NULL)
        return (-1);
    for (int i = 0; s[i]; i++) {
        if (i == 0 && s[i] == '-')
            continue;
        if ((s[i] < '0' || s[i] > '9'))
            return (-1);
    }
    return (0);
}
