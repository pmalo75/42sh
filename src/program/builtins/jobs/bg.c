/*
** EPITECH PROJECT, 2026
** G-PSU-200-PAR-2-1-42sh-10
** File description:
** bg
*/

#include "global.h"

int bg_builtin(env_t *env, char **cmd)
{
    char *temp = NULL;

    cmd++;
    if (*cmd == NULL) {
        temp = get_default_proc_arg(env->jobs);
        if (temp == NULL)
            return EXIT_FAILURE;
        restart_job(env, temp, false);
        free(temp);
    }
    while (*cmd) {
        if (restart_job(env, *cmd, false) != EXIT_SUCCESS)
            return EXIT_FAILURE;
        cmd++;
    }
    return EXIT_SUCCESS;
}
