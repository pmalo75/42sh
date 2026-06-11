/*
** EPITECH PROJECT, 2026
** my_sh
** File description:
** my_sh
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

#include "my_sh_def.h"
#include "execute.h"
#include "my.h"

static void print_signal_error(int status, char *msg)
{
    my_putsterr(msg);
    if (WCOREDUMP(status) != 0)
        my_putsterr(" (core dumped)");
    my_putsterr("\n");
}

static void check_signal(int status)
{
    if (WIFSIGNALED(status) != 0) {
        if (WTERMSIG(status) == SIGSEGV) {
            print_signal_error(status, "Segmentation fault");
            return;
        }
        if (WTERMSIG(status) == SIGABRT) {
            print_signal_error(status, "Abort");
            return;
        }
        if (WTERMSIG(status) == SIGFPE) {
            print_signal_error(status, "Floating exception");
            return;
        }
        if (WTERMSIG(status) == SIGBUS) {
            print_signal_error(status, "Bus error");
            return;
        }
    }
}

int analyse_status(int status, env_t *env, pid_t pid, char **cmd)
{
    check_signal(status);
    if (WIFEXITED(status) != 0) {
        return (WEXITSTATUS(status));
    }
    if (WIFSTOPPED(status) != 0) {
        append_job(env, pid, cmd);
        printf("Suspended\n");
        return SIGNALS_BEGIN + WSTOPSIG(status);
    }
    if (WIFSIGNALED(status) != 0)
        return SIGNALS_BEGIN + WTERMSIG(status);
    return (SUCCESS);
}

static void execute_cmd(env_t *env, char **cmd, int fd[2])
{
    if (fd[0] != -1 && fd[0] != STDIN_FILENO) {
        if (dup2(fd[0], STDIN_FILENO) == -1)
            return;
        close(fd[0]);
    }
    if (fd[1] != -1 && fd[1] != STDOUT_FILENO) {
        if (dup2(fd[1], STDOUT_FILENO) == -1)
            return;
        close(fd[1]);
    }
    signal(SIGTSTP, SIG_DFL);
    signal(SIGINT, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    execve(env->ev_path, cmd, env->ev_vars);
    exit(ERROR);
}

int execute_shell(env_t *env, char **cmd, int fd[2])
{
    int cpid = fork();

    if (cpid == -1) {
        perror("fork fail");
        return (FATAL_ERROR);
    }
    if (cpid == 0) {
        setpgid(0, (env->first_pid == 0) ? 0 : env->first_pid);
        tcsetpgrp(0, getpgrp());
        execute_cmd(env, cmd, fd);
    }
    setpgid(cpid, (env->first_pid == 0) ? cpid : env->first_pid);
    tcsetpgrp(0, (env->first_pid == 0) ? cpid : env->first_pid);
    return (cpid);
}
