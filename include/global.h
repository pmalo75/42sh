/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#ifndef GLOBAL_H_
    #define GLOBAL_H_

    #include <stdlib.h>
    #include <limits.h>
    #include <stdbool.h>
typedef enum job_state_e {
    SUSPENDED,
    RUNNING,
    DONE
} job_state_t;

typedef struct jobs_s {
    pid_t pid;
    size_t id;
    job_state_t state;
    char **cmd;
    struct jobs_s *next;
} jobs_t;

typedef struct env_s {
    char **local_vars;
    char **ev_vars;
    char ev_path[PATH_MAX];
    bool is_running;
    jobs_t *jobs;
    pid_t first_pid;
} env_t;

char *my_getenv(env_t *env, char *key);
int init_local_var(env_t *env);

int append_job(env_t *env, pid_t pid, char **cmd);
int restart_job(env_t *env, const char *arg, bool foreground);
void free_jobs(env_t *env);

size_t get_total_jobs(jobs_t *jobs);
char *get_default_proc_arg(jobs_t *jobs);

#endif /* !GLOBAL_H_ */
