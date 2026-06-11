/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "line_edition.h"
#include "autocomplete.h"

static void insert_char(line_data_t *line, char c)
{
    memmove(
        &line->buffer[line->cursor + 1],
        &line->buffer[line->cursor],
        line->len - line->cursor + 1
    );
    line->buffer[line->cursor] = c;
    line->cursor++;
    line->len++;
    line->buffer[line->len] = '\0';
}

static bool exec_keybind(line_data_t *line, char c, bool *ran)
{
    int i = 0;

    *ran = false;
    while (KEYBINDS[i].handler) {
        if (KEYBINDS[i].key == c) {
            *ran = true;
            return KEYBINDS[i].handler(line);
        }
        i++;
    }
    return false;
}

void redraw_line(const line_data_t *line)
{
    size_t i = 0;

    printf("\r");
    printf("%s", line->prompt);
    printf("%s", line->buffer);
    printf(CLEAR_LINE_SQ);
    while (i < line->len - line->cursor) {
        printf(CURSOR_LEFT_SQ);
        i++;
    }
    fflush(stdout);
}

bool handle_backspace(line_data_t *line)
{
    if (line->cursor == 0 || line->len == 0)
        return true;
    memmove(
        &line->buffer[line->cursor - 1],
        &line->buffer[line->cursor],
        line->len - line->cursor + 1
    );
    line->cursor--;
    line->len--;
    line->buffer[line->len] = '\0';
    redraw_line(line);
    return true;
}

bool handle_esc_sq(line_data_t *line)
{
    char seq[2];

    if (read(STDIN_FILENO, &seq[0], 1) <= 0)
        return true;
    if (read(STDIN_FILENO, &seq[1], 1) <= 0)
        return true;
    if (seq[1] == ARROW_LEFT && line->cursor > 0) {
        line->cursor--;
        printf(CURSOR_LEFT_SQ);
    }
    if (seq[1] == ARROW_RIGHT && line->cursor < line->len) {
        line->cursor++;
        printf(CURSOR_RIGHT_SQ);
    }
    if (seq[1] == ARROW_UP)
        return handle_history_up(line);
    if (seq[1] == ARROW_DOWN)
        return handle_history_down(line);
    fflush(stdout);
    return true;
}

bool handle_ctrl_d(line_data_t *line)
{
    if (line->len == 0) {
        line->is_eof = true;
        return false;
    }
    if (line->cursor < line->len) {
        memmove(
            &line->buffer[line->cursor],
            &line->buffer[line->cursor + 1],
            line->len - line->cursor
        );
        line->len--;
        line->buffer[line->len] = '\0';
        redraw_line(line);
    }
    return true;
}

bool handle_ctrl_c(line_data_t *line)
{
    line->len = 0;
    line->cursor = 0;
    line->buffer[0] = '\0';
    printf("\n%s", line->prompt);
    fflush(stdout);
    return true;
}

bool handle_input(env_t *env, line_data_t *line, char c)
{
    bool ran = false;
    bool status = false;

    (void)env;
    status = exec_keybind(line, c, &ran);
    if (ran)
        return status;
    if (c == NEWLINE_CHAR)
        return false;
    if (c == TAB_CHAR)
        return autocomplete(line);
    if (c < CTRL_CHAR_MAX)
        return true;
    insert_char(line, c);
    redraw_line(line);
    return true;
}
