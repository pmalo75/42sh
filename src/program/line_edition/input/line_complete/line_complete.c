/*
** EPITECH PROJECT, 2026
** G-PSU-200-PAR-2-1-42sh-10
** File description:
** autocomplete
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>

#include "line_edition.h"
#include "autocomplete.h"

static void append_compliants_in_single_path(
    const char *path,
    const char *command_begin,
    autocomplete_item_t **items
)
{
    DIR *dir = opendir(path);
    struct dirent *file = NULL;

    if (!dir)
        return;
    file = readdir(dir);
    while (file != NULL) {
        if (strncmp(file->d_name, command_begin, strlen(command_begin)) == 0)
            append_autocomplete_item(items, file->d_name);
        file = readdir(dir);
    }
    closedir(dir);
}

static void display_single_command(const char *name, const size_t len)
{
    for (size_t i = 0; i < strlen(name); i++) {
        if (i < len)
            printf("\e[0;32m%c\e[0m", name[i]);
        if (i >= len)
            printf("%c", name[i]);
    }
    printf("\n");
}

static void display_all_commands(
    const autocomplete_item_t *items,
    const size_t len
)
{
    if (items != NULL)
        printf("\n");
    while (items != NULL) {
        display_single_command(items->name, len);
        items = items->next;
    }
}

static void display_all_compliant_commands(
    const char *command_begin,
    autocomplete_item_t **items
)
{
    char *path = getenv("PATH");
    char *path_dup = NULL;
    char *token = NULL;
    char *saveptr = NULL;

    if (!path)
        return;
    path_dup = strdup(path);
    if (!path_dup)
        return;
    token = strtok_r(path_dup, ":", &saveptr);
    while (token != NULL) {
        append_compliants_in_single_path(token, command_begin, items);
        token = strtok_r(NULL, ":", &saveptr);
    }
    free(path_dup);
}

static void replace_if_single_found(
    line_data_t *line,
    const autocomplete_item_t *items
)
{
    if (!items || items->next != NULL)
        return;
    strcpy(line->buffer, items->name);
    line->cursor = strlen(items->name);
    line->len = strlen(items->name);
}

bool autocomplete(line_data_t *line)
{
    char *line_before = strdup(line->buffer);
    autocomplete_item_t *items = NULL;

    if (!line_before)
        return true;
    line_before[line->cursor] = '\0';
    display_all_compliant_commands(line_before, &items);
    display_all_commands(items, strlen(line->buffer));
    replace_if_single_found(line, items);
    free_autocomplete_items(items);
    redraw_line(line);
    free(line_before);
    return true;
}
