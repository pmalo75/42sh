/*
** EPITECH PROJECT, 2026
** my_strchr.c
** File description:
** my_strchr.c
*/

#include "my.h"
#include <stdbool.h>
int my_strchr(const char *s, char c)
{
    int find = false;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == c) {
            find = true;
            break;
        }
    }
    return (find);
}
