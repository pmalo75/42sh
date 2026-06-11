/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "history.h"

char *get_history_path(void)
{
    char *home = getenv("HOME");
    char *path = NULL;
    int len = 0;

    if (!home)
        return (NULL);
    len = snprintf(NULL, 0, "%s/.42sh_history", home);
    path = malloc(sizeof(char) * (len + 1));
    if (!path)
        return (NULL);
    snprintf(path, len + 1, "%s/.42sh_history", home);
    return (path);
}

void save_history(char *cmd)
{
    FILE *file = NULL;
    char *path = NULL;
    time_t timestamp;

    if (!cmd || cmd[0] == '\0')
        return;
    path = get_history_path();
    if (!path)
        return;
    timestamp = get_timestamp();
    file = fopen(path, "a");
    if (!file) {
        free(path);
        return;
    }
    fprintf(file, "%ld\t%s\n", timestamp, cmd);
    fclose(file);
    free(path);
}
