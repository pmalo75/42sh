/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <stdbool.h>

#include "my_sh_def.h"
#include "my_builtins.h"
#include "my.h"

int my_exit(env_t *env, char **cmd)
{
    int i = 0;

    for (; cmd[i]; i++);
    if (i >= 3) {
        my_putsterr("exit: Expression Syntax.\n");
        return (ERROR);
    }
    if (i == 2) {
        if (is_number(cmd[1]) != -1) {
            my_putstr("exit\n");
            env->is_running = false;
            return (my_getnbr(cmd[1]));
        } else {
            my_putsterr("exit: Expression Syntax.\n");
            return (ERROR);
        }
    }
    my_putstr("exit\n");
    env->is_running = false;
    return (SUCCESS);
}
