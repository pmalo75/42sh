/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include "my_sh_def.h"
#include "execute.h"

int execute_semicolon(ast_node_t *node, env_t *env, int fd[2])
{
    int d_fd[2] = {-1, -1};

    (void)fd;
    execute_ast(node->left, env, d_fd);
    execute_ast(node->right, env, d_fd);
    return SUCCESS;
}

static int manage_ret(pid_t pid_r, env_t *env, char **cmd)
{
    int status = 0;

    if (pid_r == 0)
        return SUCCESS;
    if (pid_r > 0) {
        if (waitpid(pid_r, &status, WUNTRACED) == -1)
            return pid_r;
        tcsetpgrp(0, getpgrp());
        return analyse_status(status, env, pid_r, cmd);
    }
    return ERROR;
}

static void assign_first_pid(env_t *env, pid_t pid_l)
{
    if (env->first_pid == 0)
        env->first_pid = pid_l;
}

int exec_pipe(ast_node_t *node, env_t *env, int fd[2])
{
    int d_fd[2] = {0, 0};
    pid_t pid_l = 0;
    pid_t pid_r = 0;
    int fd_l[2] = {-1, -1};
    int fd_r[2] = {-1, -1};

    if (pipe(d_fd) == -1)
        return ERROR;
    fd_l[0] = fd[0];
    fd_l[1] = d_fd[1];
    pid_l = execute_ast(node->left, env, fd_l);
    close(d_fd[1]);
    fd_r[0] = d_fd[0];
    fd_r[1] = fd[1];
    assign_first_pid(env, pid_l);
    pid_r = execute_ast(node->right, env, fd_r);
    close(d_fd[0]);
    if (pid_l > 0)
        waitpid(pid_l, NULL, WUNTRACED);
    return manage_ret(pid_r, env, node->content);
}

int exec_logic_and(ast_node_t *node, env_t *env, int fd[2])
{
    int d_fd[2] = {-1, -1};
    int ret = 0;

    (void)fd;
    ret = execute_ast(node->left, env, d_fd);
    if (ret != SUCCESS)
        return ret;
    return execute_ast(node->right, env, d_fd);
}

int exec_logic_or(ast_node_t *node, env_t *env, int fd[2])
{
    int d_fd[2] = {-1, -1};
    int ret = 0;

    (void)fd;
    ret = execute_ast(node->left, env, d_fd);
    if (ret == SUCCESS)
        return ret;
    return execute_ast(node->right, env, d_fd);
}
