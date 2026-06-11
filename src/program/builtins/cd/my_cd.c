/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include "my_sh_def.h"
#include "my_builtins.h"
#include "my.h"

int my_cd(env_t *env, char **cmd)
{
    int n = 0;

    for (; cmd[n]; n++);
    if (n > 2) {
        my_putsterr("cd: Too many arguments.\n");
        return (ERROR);
    }
    if (n == 1 || my_strcmp(cmd[1], "~") == 0) {
        return move_home(env);
    }
    if (my_strcmp(cmd[1], "-") == 0) {
        return move_old_dir(env);
    }
    return move_directory(env, cmd);
}
