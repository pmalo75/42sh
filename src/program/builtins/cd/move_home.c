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

static char *get_home_directory(env_t *env)
{
    char *home_dir = parse_arr_element(env->ev_vars, "HOME=", 5);

    if (home_dir == NULL) {
        return (NULL);
    }
    return (home_dir);
}

static int swap_pwd(env_t *env, char *old_dir, char *home_dir)
{
    if (my_setenv(env, "OLDPWD", old_dir) == ERROR)
        return (ERROR);
    if (my_setenv(env, "PWD", home_dir) == ERROR)
        return (ERROR);
    return (SUCCESS);
}

int move_home(env_t *env)
{
    char *home_dir = get_home_directory(env);
    char old_pwd[PATH_MAX];

    if (home_dir == NULL) {
        my_putsterr("cd: No home directory.\n");
        return (ERROR);
    }
    my_memset(old_pwd, 0, sizeof(old_pwd));
    if (getcwd(old_pwd, sizeof(char) * PATH_MAX) == NULL)
        return (ERROR);
    if (chdir(home_dir) == -1)
        return (ERROR);
    if (swap_pwd(env, old_pwd, home_dir) == ERROR)
        return (ERROR);
    return (SUCCESS);
}
