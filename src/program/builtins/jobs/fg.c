/*
** EPITECH PROJECT, 2026
** G-PSU-200-PAR-2-1-42sh-10
** File description:
** fg
*/

#include <stdio.h>
#include <string.h>
#include <wait.h>
#include <unistd.h>

#include "global.h"

static size_t get_last_job(jobs_t *jobs)
{
    size_t index = 1;

    while (jobs != NULL) {
        if (jobs->next == NULL)
            break;
        jobs = jobs->next;
        index++;
    }
    return index;
}

char *get_default_proc_arg(jobs_t *jobs)
{
    char *buffer = malloc((strlen("2147483647") + 2) * sizeof(char));

    if (buffer == NULL)
        return NULL;
    buffer[0] = '\0';
    sprintf(buffer, "%%%zu", get_last_job(jobs));
    return buffer;
}

int fg_builtin(env_t *env, char **cmd)
{
    char *temp = NULL;

    cmd++;
    if (*cmd == NULL) {
        temp = get_default_proc_arg(env->jobs);
        if (temp == NULL)
            return EXIT_FAILURE;
        restart_job(env, temp, true);
        free(temp);
    }
    while (*cmd) {
        if (restart_job(env, *cmd, true) != EXIT_SUCCESS)
            return EXIT_FAILURE;
        cmd++;
    }
    return EXIT_SUCCESS;
}
