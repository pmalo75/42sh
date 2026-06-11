/*
** EPITECH PROJECT, 2026
** G-PSU-200-PAR-2-1-42sh-10
** File description:
** jobs
*/

#include <stdio.h>
#include <wait.h>

#include "global.h"
#include "my.h"

size_t get_total_jobs(jobs_t *jobs)
{
    size_t count = 0;

    while (jobs != NULL) {
        jobs = jobs->next;
        count++;
    }
    return count;
}

static void display_if_last_jobs(size_t current, size_t count)
{
    if (current == count) {
        printf("+\t");
        return;
    }
    if (current == count - 1) {
        printf("-\t");
        return;
    }
    printf("\t");
}

static void display_state(jobs_t *job)
{
    switch (job->state) {
        case SUSPENDED:
            printf("Suspended");
            break;
        case RUNNING:
            printf("Running");
            break;
        case DONE:
            printf("Done");
            break;
        default:
            printf("Unknown");
            break;
    }
}

static void display_char_array(const char **cmd)
{
    while (*cmd) {
        printf(" %s", *cmd);
        cmd++;
    }
}

static void display_jobs(jobs_t *jobs)
{
    jobs_t *job = jobs;
    size_t count = get_total_jobs(jobs);

    if (jobs == NULL)
        return;
    while (job != NULL) {
        printf("[%zu]\t", job->id);
        display_if_last_jobs(job->id, count);
        display_state(job);
        printf("\t\t");
        display_char_array((const char **)job->cmd);
        printf("\n");
        job = job->next;
    }
}

static void update_job_state(jobs_t *job)
{
    int status = 0;

    if (waitpid(job->pid, &status, WNOHANG | WUNTRACED) > 0) {
        if (WIFEXITED(status) || WIFSIGNALED(status)) {
            job->state = DONE;
            return;
        }
        if (WIFSTOPPED(status)) {
            job->state = SUSPENDED;
            return;
        }
    }
}

static void update_job_states(jobs_t *jobs)
{
    while (jobs != NULL) {
        update_job_state(jobs);
        jobs = jobs->next;
    }
}

static void delete_done_jobs(jobs_t *jobs)
{
    jobs_t *job = jobs;
    jobs_t *save = NULL;

    if (jobs == NULL)
        return;
    for (; job->next != NULL; job = job->next) {
        if (job->next->state == DONE && job->next->next == NULL) {
            free_arr(job->next->cmd);
            free(job->next);
            job->next = NULL;
            break;
        }
        if (job->next->state == DONE && job->next->next != NULL) {
            save = job->next->next;
            free_arr(job->next->cmd);
            free(job->next);
            job->next = save;
            break;
        }
    }
}

static void handle_single_done_job(jobs_t **jobs)
{
    if (*jobs == NULL)
        return;
    if ((*jobs)->state == DONE) {
        free_arr((*jobs)->cmd);
        free(*jobs);
        *jobs = NULL;
    }
}

int jobs(env_t *env, char **cmd)
{
    (void)cmd;
    delete_done_jobs(env->jobs);
    handle_single_done_job(&env->jobs);
    update_job_states(env->jobs);
    display_jobs(env->jobs);
    return EXIT_SUCCESS;
}
