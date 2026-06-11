/*
** EPITECH PROJECT, 2026
** is_alpha
** File description:
** is_alpha
*/

#include "my.h"

static int is_char_alpha(char c)
{
    if (c >= 'a' && c <= 'z') {
        return EXT_SUCCESS;
    } else if (c >= 'A' && c <= 'Z') {
        return EXT_SUCCESS;
    }
    return EXT_ERROR;
}

int is_alpha(const char *s)
{
    if (s == NULL)
        return EXT_ERROR;
    for (int i = 0; s[i]; i++) {
        if (is_char_alpha(s[i]) == EXT_ERROR)
            return EXT_ERROR;
    }
    return EXT_SUCCESS;
}
