/*
** EPITECH PROJECT, 2026
** my_putnbr
** File description:
** my_putnbr
*/

#include "my.h"
#include <limits.h>

int my_putnbr(long long numb)
{
    int rest = 0;

    if (numb > INT_MAX || numb < INT_MIN)
        return EXT_ERROR;
    if (numb < 0) {
        numb *= -1;
        write(1, "-", 1);
    }
    if (numb / 10) {
        rest = numb % 10;
        numb /= 10;
        my_putnbr(numb);
        my_putchar(rest + '0');
    } else {
        my_putchar(numb + '0');
    }
    return EXT_SUCCESS;
}
