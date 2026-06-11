/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include "my_sh_def.h"
#include "checker.h"
#include "my.h"

static int build_path(env_t *env, char *path, char **cmd)
{
    if (my_strcpy(env->ev_path, path) == NULL)
        return (ERROR);
    if (my_strcat(env->ev_path, "/") == NULL)
        return (ERROR);
    if (my_strcat(env->ev_path, cmd[0]) == NULL)
        return (ERROR);
    return (SUCCESS);
}

int is_file_ok(char **path_tab, env_t *env, char **cmd)
{
    int path_len = 0;

    for (int i = 0; path_tab[i]; i++) {
        path_len = my_strlen(path_tab[i]) + 1;
        path_len += my_strlen(cmd[0]) + 1;
        if (path_len >= PATH_MAX)
            continue;
        if (build_path(env, path_tab[i], cmd) == ERROR)
            return (ERROR);
        if (access(env->ev_path, X_OK) == 0) {
            return (SUCCESS);
        }
        my_memset(env->ev_path, 0, sizeof(char) * PATH_MAX);
        path_len = 0;
    }
    return (ERROR);
}
