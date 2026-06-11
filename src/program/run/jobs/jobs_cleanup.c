/*
** EPITECH PROJECT, 2026
** G-PSU-200-PAR-2-1-42sh-10
** File description:
** jobs_cleanup
*/

#include "my.h"
#include "global.h"

void free_jobs(env_t *env)
{
    jobs_t *job = env->jobs;
    jobs_t *next_job = job;

    while (job != NULL) {
        next_job = job->next;
        free_arr(job->cmd);
        free(job);
        job = next_job;
    }
}
