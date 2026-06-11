/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "my_sh_def.h"
#include "execute.h"
#include "my_builtins.h"
#include "global.h"
#include "my.h"

static int manage_builtin(ast_node_t *node, env_t *env, int fd[2])
{
    if (fd[0] != -1) {
        if (dup2(fd[0], STDIN_FILENO) == -1)
            return ERROR;
    }
    if (fd[1] != -1) {
        if (dup2(fd[1], STDOUT_FILENO) == -1)
            return ERROR;
    }
    for (size_t i = 0; BUILTINS[i].name; i++) {
        if (my_strcmp(BUILTINS[i].name, node->content[0]) == 0) {
            return (BUILTINS[i].func(env, node->content));
        }
    }
    return ERROR;
}

int exec_builtins(ast_node_t *node, env_t *env, int fd[2])
{
    int ret = 0;
    int save_in = dup(STDIN_FILENO);
    int save_out = dup(STDOUT_FILENO);

    if (save_in == -1 || save_out == -1)
        return ERROR;
    ret = manage_builtin(node, env, fd);
    if (dup2(save_in, STDIN_FILENO) == -1)
        return ERROR;
    close(save_in);
    if (dup2(save_out, STDOUT_FILENO) == -1)
        return ERROR;
    close(save_out);
    return ret;
}
