/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "my.h"
#include "my_sh_def.h"
#include "history.h"
#include "my_builtins.h"

static void display_entry(char *line, int i)
{
    char **parts = str_to_word_array(line, "\t");
    time_t timestamp = {0};
    struct tm *time_info = NULL;

    if (!parts || !parts[0] || !parts[1]) {
        free_arr(parts);
        return;
    }
    timestamp = atol(parts[0]);
    time_info = localtime(&timestamp);
    printf("%d\t%02d:%02d\t%s",
        i,
        time_info->tm_hour,
        time_info->tm_min,
        parts[1]);
    free_arr(parts);
}

static int open_history(FILE **file, char **path)
{
    *path = get_history_path();
    if (!(*path))
        return ERROR;
    *file = fopen(*path, "r");
    if (!(*file)) {
        free(*path);
        return ERROR;
    }
    return SUCCESS;
}

static void read_history(FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    int i = START;

    while (getline(&line, &len, file) != EOF) {
        display_entry(line, i);
        i++;
    }
    free(line);
}

int my_history(env_t *env, char **args)
{
    FILE *file = NULL;
    char *path = NULL;

    (void)env;
    (void)args;
    if (open_history(&file, &path) == ERROR)
        return SUCCESS;
    read_history(file);
    fclose(file);
    free(path);
    return SUCCESS;
}
