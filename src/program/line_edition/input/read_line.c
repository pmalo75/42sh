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

#include "line_edition.h"
#include "execute.h"
#include "my.h"

static char *resz_buffer(line_data_t *line)
{
    char *new_buffer = NULL;

    line->capacity *= 2;
    new_buffer = realloc(line->buffer, line->capacity);
    if (!new_buffer) {
        free(line->buffer);
        return NULL;
    }
    line->buffer = new_buffer;
    return new_buffer;
}

static bool check_resize(line_data_t *line)
{
    if (line->len + 1 < line->capacity)
        return true;
    return resz_buffer(line) != NULL;
}

static bool read_input(env_t *env, line_data_t *line)
{
    char c;

    if (read(STDIN_FILENO, &c, 1) <= 0)
        return false;
    if (!check_resize(line))
        return false;
    return handle_input(env, line, c);
}

static void init_line_data(env_t *env, line_data_t *line)
{
    line->len = 0;
    line->cursor = 0;
    line->capacity = INIT_BUF_SZ;
    line->buffer = calloc(line->capacity, sizeof(char));
    line->prompt = get_prompt(env);
    line->history = load_history();
    line->history_index = 0;
    if (line->history)
        line->history_index = get_history_size(line->history);
}

char *read_line(env_t *env)
{
    line_data_t line = {0};

    init_line_data(env, &line);
    if (!line.buffer || !line.prompt)
        return NULL;
    printf("%s", line.prompt);
    fflush(stdout);
    while (read_input(env, &line))
        continue;
    if (line.is_eof) {
        free(line.buffer);
        free(line.prompt);
        free_arr(line.history);
        return NULL;
    }
    line.buffer[line.len] = '\0';
    putchar('\n');
    free(line.prompt);
    free_arr(line.history);
    return line.buffer;
}
