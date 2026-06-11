/*
** EPITECH PROJECT, 2025
** get_nbr
** File description:
** get_nbr
*/

#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int handle_error(long result)
{
    if (result < INT_MIN || result > INT_MAX) {
        return 0;
    }
    return (int)result;
}

int my_getnbr(const char *str)
{
    int i = 0;
    long result = 0;
    int sign = 1;

    if ((str[i] < '0' || str[i] > '9') && (str[i] != '-'))
        return 0;
    if (str[i] == '-') {
        sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    result = result * sign;
    return handle_error(result);
}
