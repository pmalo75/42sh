/*
** EPITECH PROJECT, 2026
** lib
** File description:
** lib
*/

#include "my.h"

void free_arr(char **arr)
{
    if (!arr)
        return;
    for (int i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    free(arr);
}
