/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include "my_sh_def.h"
#include "my_builtins.h"
#include "my.h"

#include <limits.h>

static char *get_old_directory(env_t *env)
{
    char *old_dir = parse_arr_element(env->ev_vars, "OLDPWD=", 7);

    if (old_dir == NULL)
        (NULL);
    return (old_dir);
}

static int swap_pwd(env_t *env, char *curr_dir, char *old_dir)
{
    if (my_setenv(env, "OLDPWD", curr_dir) == ERROR)
        return (ERROR);
    if (my_setenv(env, "PWD", old_dir) == ERROR)
        return (ERROR);
    return (SUCCESS);
}

int move_old_dir(env_t *env)
{
    char *old_dir = get_old_directory(env);
    char curr_dir[PATH_MAX];

    if (old_dir == NULL) {
        my_putsterr(": No such file or directory.\n");
        return (ERROR);
    }
    if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
        return (ERROR);
    if (chdir(old_dir) == -1)
        return (ERROR);
    if (swap_pwd(env, curr_dir, old_dir) == ERROR)
        return (ERROR);
    return (SUCCESS);
}
