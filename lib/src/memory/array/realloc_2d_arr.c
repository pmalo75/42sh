/*
** EPITECH PROJECT, 2026
** realloc_2d_arr
** File description:
** realloc_2d_arr
*/

#include "my.h"

char **realloc_2d_arr(char **src, char *new_element_to_add)
{
    int tab_len = 0;
    char **new_tab = NULL;
    int i = 0;

    for (; src && src[tab_len]; tab_len++);
    new_tab = malloc((tab_len + 2) * sizeof(char *));
    if (!new_tab)
        return NULL;
    for (; i < tab_len; i++) {
        new_tab[i] = src[i];
    }
    new_tab[i] = new_element_to_add;
    i++;
    new_tab[i] = NULL;
    if (src)
        free(src);
    return new_tab;
}
