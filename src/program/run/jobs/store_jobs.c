/*
** EPITECH PROJECT, 2026
** G-PSU-200-PAR-2-1-42sh-10
** File description:
** store_jobs
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>

#include "global.h"

char **duplicate_char_array(char **base_array)
{
    char **array = NULL;
    size_t length = 0;

    if (base_array == NULL)
        return NULL;
    while (base_array[length] != NULL)
        length++;
    array = calloc((length + 1), sizeof(char *));
    if (array == NULL)
        return NULL;
    for (size_t i = 0; base_array[i] != NULL; i++) {
        array[i] = strdup(base_array[i]);
        if (array[i] == NULL)
            return NULL;
    }
    array[length] = NULL;
    return array;
}

static bool handle_pid_already_exists(jobs_t *jobs, pid_t pid)
{
    while (jobs != NULL) {
        if (jobs->pid == pid) {
            jobs->state = SUSPENDED;
            return true;
        }
        jobs = jobs->next;
    }
    return false;
}

static jobs_t *create_new_job(pid_t pid, char **cmd)
{
    jobs_t *job = calloc(1, sizeof(jobs_t));

    if (job == NULL)
        return NULL;
    job->pid = pid;
    job->cmd = duplicate_char_array(cmd);
    if (job->cmd == NULL) {
        free(job);
        return NULL;
    }
    job->id = 1;
    return job;
}

static void append_to_the_end(env_t *env, jobs_t *new_job)
{
    jobs_t *job = env->jobs;

    while (job->next != NULL) {
        job = job->next;
    }
    new_job->id = job->id + 1;
    job->next = new_job;
}

int append_job(env_t *env, pid_t pid, char **cmd)
{
    jobs_t *job = NULL;

    if (handle_pid_already_exists(env->jobs, pid))
        return EXIT_SUCCESS;
    job = create_new_job(pid, cmd);
    if (job == NULL)
        return EXIT_FAILURE;
    if (env->jobs == NULL) {
        env->jobs = job;
        return EXIT_SUCCESS;
    }
    append_to_the_end(env, job);
    return EXIT_SUCCESS;
}
