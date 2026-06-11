/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#ifndef EXECUTE_H_
    #define EXECUTE_H_
    #define SIGNALS_BEGIN 128

    #include "parser.h"
    #include "global.h"

// Signal
int analyse_status(int status, env_t *env, pid_t pid, char **cmd);

int execute_ast(ast_node_t *node, env_t *env, int fd[2]);

// Program >> run
int execute_shell(env_t *env, char **cmd, int fd[2]);
int exec_builtins(ast_node_t *node, env_t *env, int fd[2]);
int init_shell(char **envp);
void display_prompt(env_t *env);

typedef int (*exec_func_t)(ast_node_t *node, env_t *env);

// Operators rules
int execute_semicolon(ast_node_t *node, env_t *env, int fd[2]);
int exec_pipe(ast_node_t *node, env_t *env, int fd[2]);
int exec_right_red(ast_node_t *node, env_t *env, int fd[2]);
int exec_red_right_app(ast_node_t *node, env_t *env, int fd[2]);
int exec_red_left(ast_node_t *node, env_t *env, int fd[2]);
int heredoc(ast_node_t *node, env_t *env, int fd[2]);
int exec_logic_and(ast_node_t *node, env_t *env, int fd[2]);
int exec_logic_or(ast_node_t *node, env_t *env, int fd[2]);

typedef int (*exec_op_t)(ast_node_t *node, env_t *env, int fd[2]);

typedef struct rules_s {
    action_t op;
    exec_op_t run;
} rules_t;

static const rules_t RULES[] = {
    {SEMICOLON, execute_semicolon},
    {PIPE, exec_pipe},
    {RED_RIGHT, exec_right_red},
    {RED_RIGHT_APP, exec_red_right_app},
    {RED_LEFT, exec_red_left},
    {HEREDOC, heredoc},
    {LOGIC_AND, exec_logic_and},
    {LOGIC_OR, exec_logic_or},
    {CONTENT, NULL}
};

#endif /* !EXECUTE_H_ */
