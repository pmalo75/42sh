/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "my_sh_def.h"
#include "execute.h"
#include "my.h"

int exec_right_red(ast_node_t *node, env_t *env, int fd[2])
{
    int file = 0;
    pid_t pid = 0;
    int d_fd[2];
    int status = 0;

    file = open(*node->right->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (file == -1)
        return ERROR;
    d_fd[0] = fd[0];
    d_fd[1] = file;
    pid = execute_ast(node->left, env, d_fd);
    close(file);
    if (pid > 0) {
        waitpid(pid, &status, WUNTRACED);
        return analyse_status(status, env, pid, node->content);
    }
    return pid;
}

int exec_red_right_app(ast_node_t *node, env_t *env, int fd[2])
{
    int file = 0;
    pid_t pid = 0;
    int d_fd[2];
    int status = 0;

    file = open(*node->right->content, O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (file == -1)
        return ERROR;
    d_fd[0] = fd[0];
    d_fd[1] = file;
    pid = execute_ast(node->left, env, d_fd);
    close(file);
    if (pid > 0) {
        waitpid(pid, &status, WUNTRACED);
        return analyse_status(status, env, pid, node->left->content);
    }
    return pid;
}

int exec_red_left(ast_node_t *node, env_t *env, int fd[2])
{
    int file = 0;
    pid_t pid = 0;
    int d_fd[2];
    int status = 0;

    file = open(*node->right->content, O_RDONLY);
    if (file == -1)
        return ERROR;
    d_fd[0] = file;
    d_fd[1] = fd[1];
    pid = execute_ast(node->left, env, d_fd);
    close(file);
    if (pid > 0) {
        waitpid(pid, &status, WUNTRACED);
        return analyse_status(status, env, pid, node->left->content);
    }
    return pid;
}

static int get_input(char *stop, int out_fd)
{
    ssize_t rd = 0;
    size_t sz = 0;
    char *input = NULL;

    while (rd != -1) {
        my_putstr("? ");
        rd = getline(&input, &sz, stdin);
        if (input[rd - 1] == '\n')
            input[rd - 1] = '\0';
        if (my_strcmp(stop, input) == 0)
            break;
        if (write(out_fd, input, rd - 1) == -1) {
            free(input);
            return -1;
        }
        write(out_fd, "\n", 1);
    }
    free(input);
    return 0;
}

int heredoc(ast_node_t *node, env_t *env, int fd[2])
{
    int d_fd[2] = {0, 0};
    pid_t pid = 0;
    int fd_l[2] = {0, 0};
    int status = 0;

    if (pipe(d_fd) == -1)
        return ERROR;
    if (get_input(*node->right->content, d_fd[1]) == -1)
        return ERROR;
    close(d_fd[1]);
    fd_l[0] = d_fd[0];
    fd_l[1] = fd[1];
    pid = execute_ast(node->left, env, fd_l);
    close(d_fd[0]);
    if (pid > 0) {
        waitpid(pid, &status, WUNTRACED);
        return analyse_status(status, env, pid, node->right->content);
    }
    return pid;
}
