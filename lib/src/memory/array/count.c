/*
** EPITECH PROJECT, 2026
** count array
** File description:
** count array
*/

#include "my.h"

int count_2d_arr(char **arr)
{
    int n = 0;

    if (arr == NULL)
        return -1;
    for (; arr[n]; n++);
    return n;
}
