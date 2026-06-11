/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** An integrated videoplayer.
** This requires the libav* libraries.
*/
#include <stdarg.h>
#include <stdio.h>

void display_text(char *level, int nb, ...)
{
    va_list args;

    va_start(args, nb);
    printf("[%s]\t\t", level);
    for (int i = 0; i < nb; ++i) {
        printf("%s", va_arg(args, char*));
    }
    printf("\n");
    va_end(args);
}
