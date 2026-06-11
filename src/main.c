/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <signal.h>
#include <unistd.h>

#include "my_sh_def.h"
#include "execute.h"

static void setup_job_control(void)
{
    if (isatty(STDIN_FILENO) == 0)
        return;
    setpgid(0, 0);
    tcsetpgrp(STDIN_FILENO, getpgrp());
}

int main(int argc, char **argv, char **envp)
{
    (void)argv;
    if (argc != 1)
        return (FATAL_ERROR);
    if (envp == NULL)
        return (FATAL_ERROR);
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    setup_job_control();
    return (init_shell(envp));
}
