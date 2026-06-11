/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <sys/types.h>
#include <stdbool.h>
#include <sys/wait.h>

#include "my_sh_def.h"
#include "line_edition.h"
#include "execute.h"
#include "history.h"
#include "my.h"

static int run_process(env_t *env, const char *prompt)
{
    token_bundle_t *bundle = lexer_input(prompt, env);
    ast_node_t *ast = NULL;
    int ret = 0;
    int fd[2] = {-1, -1};

    env->first_pid = 0;
    if (bundle == NULL)
        return ERROR;
    ast = parser_input(bundle);
    if (ast == NULL) {
        free_token_bundle(bundle);
        return SUCCESS;
    }
    ret = execute_ast(ast, env, fd);
    free_ast(ast);
    free_token_bundle(bundle);
    return ret;
}

static int process_in(env_t *env, terminal_t *term)
{
    char *prompt = NULL;
    int ret = 0;

    prompt = read_line(env);
    if (!prompt) {
        write(1, "exit\n", 5);
        return NORMAL_EXIT;
    }
    save_history(prompt);
    disable_raw_mode(term);
    ret = run_process(env, prompt);
    enable_raw_mode(term);
    free(prompt);
    return ret;
}

static int run_shell(env_t *env, terminal_t *term)
{
    int ret = 0;

    enable_raw_mode(term);
    while (env->is_running == true) {
        ret = process_in(env, term);
        if (ret == FATAL_ERROR || ret == NORMAL_EXIT)
            break;
    }
    disable_raw_mode(term);
    return ret != NORMAL_EXIT ? ret : SUCCESS;
}

static int launch_shell(env_t *env)
{
    terminal_t term;
    int ret = 0;

    ret = run_shell(env, &term);
    free_arr(env->ev_vars);
    free_jobs(env);
    return ret;
}

int init_shell(char **envp)
{
    env_t env = {0};

    if (envp == NULL)
        return SUCCESS;
    my_memset(&env, 0, sizeof(env));
    env.is_running = 1;
    env.ev_vars = fill_2d_arr(envp);
    if (env.ev_vars == NULL)
        return ERROR;
    return launch_shell(&env);
}
