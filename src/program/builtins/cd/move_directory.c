/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include "my_sh_def.h"
#include "my_builtins.h"
#include "my.h"

#include <sys/stat.h>
#include <limits.h>

static int is_value_ok(char *value)
{
    struct stat info;

    if (stat(value, &info) == -1) {
        my_putsterr(value);
        my_putsterr(": No such file or directory.\n");
        return (-1);
    }
    if (S_ISDIR(info.st_mode) == 0) {
        my_putsterr(value);
        my_putsterr(": Not a directory.\n");
        return (-1);
    }
    if (access(value, X_OK) != 0) {
        my_putsterr(value);
        my_putsterr(": Permission denied.\n");
        return (-1);
    }
    return (0);
}

static int swap_pwd(env_t *env, char *curr_dir)
{
    char new_dir[PATH_MAX];

    if (my_setenv(env, "OLDPWD", curr_dir) == ERROR)
        return (ERROR);
    my_memset(new_dir, 0, sizeof(new_dir));
    if (getcwd(new_dir, sizeof(new_dir)) == NULL)
        return (ERROR);
    if (my_setenv(env, "PWD", new_dir) == ERROR)
        return (ERROR);
    return (SUCCESS);
}

int move_directory(env_t *env, char **cmd)
{
    char curr_dir[PATH_MAX];

    if (is_value_ok(cmd[1]) == -1)
        return (ERROR);
    my_memset(curr_dir, 0, sizeof(curr_dir));
    if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
        return (ERROR);
    if (chdir(cmd[1]) == -1)
        return (ERROR);
    if (swap_pwd(env, curr_dir) == ERROR)
        return (ERROR);
    return (SUCCESS);
}
