/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "my_sh_def.h"
#include "execute.h"
#include "my_builtins.h"
#include "checker.h"
#include "global.h"
#include "my.h"

int exec_content(ast_node_t *node, env_t *env, int fd[2])
{
    pid_t pid = 0;
    int status = 0;

    if (get_cmd_path(env, node->content) == ERROR)
        return (ERROR);
    pid = execute_shell(env, node->content, fd);
    if (pid == ERROR)
        return ERROR;
    if (fd[0] != -1 || fd[1] != -1)
        return pid;
    waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(0, getpgrp());
    return analyse_status(status, env, pid, node->content);
}

static bool is_builtin(char *cmd)
{
    for (size_t i = 0; BUILTINS[i].name != NULL; i++) {
        if (my_strcmp(BUILTINS[i].name, cmd) == 0)
            return true;
    }
    return false;
}

int execute_ast(ast_node_t *node, env_t *env, int fd[2])
{
    if (node == NULL)
        return SUCCESS;
    if (node->type == CONTENT) {
        if (is_builtin(node->content[0]) == true)
            return exec_builtins(node, env, fd);
        return exec_content(node, env, fd);
    }
    for (size_t i = 0; RULES[i].op != CONTENT; i++) {
        if (RULES[i].op == node->type)
            return RULES[i].run(node, env, fd);
    }
    return SUCCESS;
}
