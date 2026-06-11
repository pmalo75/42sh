/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include "my_sh_def.h"
#include "my_builtins.h"
#include "my.h"

int my_env(env_t *env, char **cmd)
{
    int n = 0;

    for (; cmd[n]; n++);
    if (n != 1)
        return (ERROR);
    for (int i = 0; env->ev_vars[i]; i++) {
        my_putstr(env->ev_vars[i]);
        my_putchar('\n');
    }
    return (SUCCESS);
}
