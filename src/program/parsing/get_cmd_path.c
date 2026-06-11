/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/
#include <stdbool.h>
#include <sys/stat.h>

#include "my_sh_def.h"
#include "checker.h"
#include "global.h"
#include "my.h"

static int handle_permissions(env_t *env, char *path)
{
    struct stat info;

    stat(path, &info);
    if (S_ISDIR(info.st_mode) != 0) {
        my_putsterr(path);
        my_putsterr(": Permission denied.\n");
        return (ERROR);
    }
    if (access(path, X_OK) != 0) {
        my_putsterr(path);
        my_putsterr(": Permission denied.\n");
        return (ERROR);
    }
    if (my_strcpy(env->ev_path, path) == NULL)
        return (ERROR);
    return (SUCCESS);
}

static int is_given_path_ok(env_t *env, char **cmd)
{
    if (access(cmd[0], F_OK) == 0) {
        return handle_permissions(env, cmd[0]);
    }
    my_putsterr(cmd[0]);
    my_putsterr(": Command not found.\n");
    return (ERROR);
}

static int parse_path(
    char **path_tab, env_t *env, char **cmd)
{
    int ret = 0;

    if (my_strchr(cmd[0], '/') == false) {
        ret = is_file_ok(path_tab, env, cmd);
        if (ret == ERROR) {
            my_putsterr(cmd[0]);
            my_putsterr(": Command not found.\n");
            return (ERROR);
        }
    } else {
        return is_given_path_ok(env, cmd);
    }
    return (SUCCESS);
}

int get_cmd_path(env_t *env, char **cmd)
{
    int ret = 0;
    char **path_tab = NULL;

    if (env == NULL)
        return (ERROR);
    path_tab = get_path_values(env);
    if (path_tab == NULL)
        return (is_given_path_ok(env, cmd));
    ret = parse_path(path_tab, env, cmd);
    free_arr(path_tab);
    if (ret == ERROR)
        return (ERROR);
    return (SUCCESS);
}
