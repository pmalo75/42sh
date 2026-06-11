/*
** EPITECH PROJECT, 2025
** strcmp
** File description:
** Reproduce the behavior of the strcmp function.
*/

#include "my.h"

int my_strcmp(const char *s1, const char *s2)
{
    int rest = 0;

    for (int i = 0; s1[i] != '\0' || s2[i] != '\0'; i++) {
        if ((unsigned char)s1[i] != (unsigned char)s2[i]) {
            rest = (unsigned char)s1[i] - (unsigned char)s2[i];
            break;
        }
    }
    return rest;
}
