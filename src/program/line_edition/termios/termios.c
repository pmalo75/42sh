/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <termios.h>
#include <unistd.h>

#include "line_edition.h"

void enable_raw_mode(terminal_t *term)
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, &term->old_term);
    raw = term->old_term;
    raw.c_lflag &= ~(ICANON | ECHO | ISIG);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode(terminal_t *term)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->old_term);
}
