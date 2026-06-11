/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_analyse_status
*/

#include <criterion/criterion.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include "execute.h"

Test(analyse_status, normal_exit_zero)
{
    int status = 0;

    if (WIFEXITED(status))
        cr_assert_eq(analyse_status(status, NULL, 0, NULL), 0);
}

Test(analyse_status, normal_exit_nonzero)
{
    pid_t pid = fork();

    if (pid == 0) {
        exit(42);
    }
    int status = 0;

    waitpid(pid, &status, 0);
    cr_assert_eq(analyse_status(status, NULL, 0, NULL), 42);
}

Test(analyse_status, normal_exit_one)
{
    pid_t pid = fork();

    if (pid == 0) {
        exit(1);
    }
    int status = 0;

    waitpid(pid, &status, 0);
    cr_assert_eq(analyse_status(status, NULL, 0, NULL), 1);
}

Test(analyse_status, signal_segfault)
{
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGSEGV);
        _exit(1);
    }
    int status = 0;

    waitpid(pid, &status, 0);
    cr_assert_eq(analyse_status(status, NULL, 0, NULL), 128 + SIGSEGV);
}

Test(analyse_status, signal_abort)
{
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGABRT);
        exit(1);
    }
    int status = 0;

    waitpid(pid, &status, 0);
    cr_assert_eq(analyse_status(status, NULL, 0, NULL), 128 + SIGABRT);
}

Test(analyse_status, signal_fpe)
{
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGFPE);
        exit(1);
    }
    int status = 0;

    waitpid(pid, &status, 0);
    cr_assert_eq(analyse_status(status, NULL, 0, NULL), 128 + SIGFPE);
}

Test(analyse_status, signal_bus)
{
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGBUS);
        exit(1);
    }
    int status = 0;

    waitpid(pid, &status, 0);
    cr_assert_eq(analyse_status(status, NULL, 0, NULL), 128 + SIGBUS);
}
