/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** An integrated videoplayer.
** This requires the libav* libraries.
*/

#include <termios.h>
#include <unistd.h>

#include "mediaplayer.h"

void mpl_input_begin(struct termios *saved)
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, saved);
    raw = *saved;
    raw.c_lflag &= ~(ICANON | ECHO | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void mpl_input_end(const struct termios *saved)
{
    tcsetattr(STDIN_FILENO, TCSANOW, saved);
}

bool mpl_should_stop(void)
{
    unsigned char c = 0;

    if (read(STDIN_FILENO, &c, 1) == 1 && (c == 3 || c == 'q'))
        return true;
    return false;
}
