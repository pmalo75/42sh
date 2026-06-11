/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Credits command
*/

#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

#include "my_builtins.h"
#include "global.h"
#include "my.h"

static bool does_file_exists_in_dir(char *directory, char *filename)
{
    DIR *opened_dir = opendir(directory);
    struct dirent *current_dir = NULL;

    if (!opened_dir)
        return false;
    if (!filename) {
        closedir(opened_dir);
        return false;
    }
    current_dir = readdir(opened_dir);
    while (current_dir != NULL) {
        if (strcmp(current_dir->d_name, filename) == STRING_EQUAL) {
            closedir(opened_dir);
            return true;
        }
        current_dir = readdir(opened_dir);
    }
    closedir(opened_dir);
    return false;
}

static char *build_path(char *dir, char *filename)
{
    char *complete_fn = calloc((strlen(dir) + strlen(filename) + 2),
        sizeof(char));

    if (!complete_fn)
        return NULL;
    strcat(complete_fn, dir);
    strcat(complete_fn, "/");
    strcat(complete_fn, filename);
    strcat(complete_fn, "\0");
    return complete_fn;
}

static void display_file(char *fullpath, size_t padding)
{
    FILE *fp = fopen(fullpath, "r");
    char *line = NULL;
    size_t size = 0;

    if (!fp) {
        printf("Couldn't open file.\n");
        free(fullpath);
        return;
    }
    for (; getline(&line, &size, fp) != EOF;) {
        if (strlen(line) > 0 && line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        for (size_t i = 0; i != padding; ++i) {
            printf(" ");
        }
        printf("%s\n", line);
    }
    fclose(fp);
    free(fullpath);
    free(line);
}

static void display_images(void)
{
    char *path = NULL;

    if (does_file_exists_in_dir((char *)GROUPDIR, (char *)TEAM_MEMBERS_ASCII)) {
        path = build_path((char *)GROUPDIR, (char *)TEAM_MEMBERS_ASCII);
        if (!path || path[0] == '\0')
            return;
        printf("\x1b[2J\x1b[H");
        display_file(path, 30 + 0);
    } else {
        printf("Couldn't get the display. But it's a cool team !\n");
    }
}

static void display_nfo(void)
{
    char *path = NULL;

    if (does_file_exists_in_dir((char *)GROUPDIR, (char *)NFO)) {
        path = build_path((char *)GROUPDIR, (char *)NFO);
        if (!path)
            return;
        display_file(path, 30 + 10);
    } else {
        printf("Couldn't get the NFO. But it's a cool team !\n");
    }
}

static char *find_user(char **cmd)
{
    for (size_t userID = 0; users[userID].name; ++userID) {
        if (strcmp(cmd[1], users[userID].name) == STRING_EQUAL)
            return (users[userID].filename);
        if (strcmp(cmd[1], users[userID].email) == STRING_EQUAL)
            return (users[userID].filename);
    }
    return NULL;
}

static char *find_desc(char **cmd)
{
    for (size_t userID = 0; users[userID].name; ++userID) {
        if (strcmp(cmd[1], users[userID].name) == STRING_EQUAL)
            return (users[userID].description);
        if (strcmp(cmd[1], users[userID].email) == STRING_EQUAL)
            return (users[userID].description);
    }
    return NULL;
}

void interprete_command(char **cmd)
{
    char *targetuser = find_user(cmd);
    char *desc = find_desc(cmd);
    char *path = NULL;

    if (targetuser) {
        if (does_file_exists_in_dir((char *)PERSOGROUP,
                targetuser))
            path = build_path((char *)PERSOGROUP, targetuser);
        if (!path) {
            display_images();
            display_nfo();
        }
        printf("\x1b[2J\x1b[H");
        display_file(path, 30);
        printf("                               %s\n\n\n", desc);
    } else {
        display_images();
        display_nfo();
    }
}

int credits(env_t *env, char **cmd)
{
    (void) env;
    if (count_2d_arr(cmd) > 1) {
        interprete_command(cmd);
        return 42;
    }
    display_images();
    display_nfo();
    return 42;
}
