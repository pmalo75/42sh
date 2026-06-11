/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include "line_edition.h"

bool handle_history_up(line_data_t *line)
{
    if (!line->history)
        return true;
    if (line->history_index <= 0)
        return true;
    line->history_index--;
    strcpy(
        line->buffer,
        line->history[line->history_index]
    );
    line->len = strlen(line->buffer);
    line->cursor = line->len;
    redraw_line(line);
    return true;
}

bool handle_history_down(line_data_t *line)
{
    if (!line->history)
        return true;
    if (!line->history[line->history_index + 1])
        return true;
    line->history_index++;
    strcpy(
        line->buffer,
        line->history[line->history_index]
    );
    line->len = strlen(line->buffer);
    line->cursor = line->len;
    redraw_line(line);
    return true;
}
