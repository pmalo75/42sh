/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <time.h>

#include "history.h"

time_t get_timestamp(void)
{
    return time(NULL);
}
