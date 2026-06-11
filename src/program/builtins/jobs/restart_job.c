/*
** EPITECH PROJECT, 2026
** G-PSU-200-PAR-2-1-42sh-10
** File description:
** restart_job
*/

#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <wait.h>

#include "global.h"
#include "execute.h"
#include "my.h"

static size_t to_size_t(const char *str)
{
    char *end = NULL;
    size_t value = strtoul(str, &end, 10);

    errno = 0;
    if (errno != 0 || end == str || *end != '\0')
        return 0;
    return value;
}

static int handle_errors(const char *arg, bool foreground)
{
    char *command = foreground ? "fg" : "bg";

    if (*arg != '%') {
        printf("%s: No such job.\n", command);
        return EXIT_FAILURE;
    }
    arg++;
    if (is_number(arg) != 0) {
        printf("%s: No such job.\n", command);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static job_state_t get_job_state(int status)
{
    if (WIFEXITED(status) || WIFSIGNALED(status)) {
        return DONE;
    }
    if (WIFSTOPPED(status))
        return SUSPENDED;
    return RUNNING;
}

static int restart_target_job(jobs_t *job, bool foreground, env_t *env)
{
    int status = 0;

    if (foreground)
        tcsetpgrp(0, job->pid);
    kill(-job->pid, SIGCONT);
    if (foreground) {
        waitpid(-job->pid, &status, WUNTRACED);
        job->state = get_job_state(status);
        tcsetpgrp(0, getpgrp());
    } else {
        job->state = RUNNING;
    }
    return analyse_status(status, env, job->pid, job->cmd);
}

static void display_job_to_restart(jobs_t *job, bool foreground)
{
    printf("[%zu]   ", job->id);
    for (size_t i = 0; job->cmd[i] != NULL; i++) {
        printf("%s ", job->cmd[i]);
    }
    if (!foreground)
        printf(" &");
    printf("\n");
}

int restart_job(env_t *env, const char *arg, bool foreground)
{
    jobs_t *job = env->jobs;
    size_t target_id = 0;

    if (handle_errors(arg, foreground) != EXIT_SUCCESS)
        return EXIT_FAILURE;
    arg++;
    target_id = to_size_t(arg);
    while (job != NULL) {
        if (job->id == target_id) {
            display_job_to_restart(job, foreground);
            return restart_target_job(job, foreground, env);
        }
        job = job->next;
    }
    printf("%s: No such job.\n", foreground ? "fg" : "bg");
    return EXIT_FAILURE;
}
