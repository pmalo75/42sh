/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "line_edition.h"
#include "history.h"
#include "my.h"

static FILE *open_history(void)
{
    FILE *file = NULL;
    char *path = NULL;

    path = get_history_path();
    if (!path)
        return NULL;
    file = fopen(path, "r");
    free(path);
    return file;
}

static char **add_history(char **history, char *line, int *i)
{
    char **parts = NULL;

    parts = str_to_word_array(line, "\t");
    if (parts && parts[1]) {
        parts[1][strcspn(parts[1], "\n")] = '\0';
        history[*i] = strdup(parts[1]);
        (*i)++;
    }
    free_arr(parts);
    return history;
}

static char **init_history(FILE *file)
{
    char **history = NULL;

    history = malloc(sizeof(char *) * 1024);
    if (!history) {
        fclose(file);
        return NULL;
    }
    return history;
}

char **load_history(void)
{
    FILE *file = NULL;
    char *line = NULL;
    char **history = NULL;
    size_t len = 0;
    int i = 0;

    file = open_history();
    if (!file)
        return NULL;
    history = init_history(file);
    if (!history)
        return NULL;
    while (getline(&line, &len, file) != EOF)
        add_history(history, line, &i);
    history[i] = NULL;
    free(line);
    fclose(file);
    return history;
}

int get_history_size(char **history)
{
    int i = 0;

    if (!history)
        return 0;
    while (history[i])
        i++;
    return i;
}
