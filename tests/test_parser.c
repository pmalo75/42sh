/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_parser
*/

#include <criterion/criterion.h>
#include "parser.h"
#include "lexer.h"
#include "my.h"

static env_t create_parser_env(void)
{
    env_t env = {0};
    char **vars = malloc(sizeof(char *) * 2);

    vars[0] = my_strdup("PATH=/usr/bin:/bin");
    vars[1] = NULL;
    env.ev_vars = vars;
    env.ev_path[0] = '\0';
    return env;
}

Test(parser_input, null_bundle_returns_null)
{
    ast_node_t *result = parser_input(NULL);

    cr_assert_null(result);
}

Test(parser_input, empty_bundle_returns_null)
{
    token_bundle_t bundle = {0};

    bundle.tokens = malloc(sizeof(char *));
    bundle.tokens[0] = NULL;
    bundle.weights = malloc(sizeof(int));
    bundle.weights[0] = 0;
    bundle.count = 0;
    bundle.cap = 1;

    ast_node_t *result = parser_input(&bundle);

    cr_assert_null(result);
    free(bundle.tokens);
    free(bundle.weights);
}

Test(parser_input, single_command_creates_leaf)
{
    env_t env = create_parser_env();
    token_bundle_t *bundle = lexer_input("ls", &env);

    cr_assert_not_null(bundle);

    ast_node_t *ast = parser_input(bundle);

    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, CONTENT);
    cr_assert_str_eq(ast->content[0], "ls");
    cr_assert_null(ast->left);
    cr_assert_null(ast->right);
    free_ast(ast);
    free_token_bundle(bundle);
    free_arr(env.ev_vars);
}

Test(parser_input, command_with_args_creates_leaf)
{
    env_t env = create_parser_env();
    token_bundle_t *bundle = lexer_input("ls -la /tmp", &env);

    cr_assert_not_null(bundle);

    ast_node_t *ast = parser_input(bundle);

    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, CONTENT);
    cr_assert_str_eq(ast->content[0], "ls");
    cr_assert_str_eq(ast->content[1], "-la");
    cr_assert_str_eq(ast->content[2], "/tmp");
    free_ast(ast);
    free_token_bundle(bundle);
    free_arr(env.ev_vars);
}

Test(parser_input, pipe_creates_tree)
{
    env_t env = create_parser_env();
    token_bundle_t *bundle = lexer_input("ls | cat", &env);

    cr_assert_not_null(bundle);

    ast_node_t *ast = parser_input(bundle);

    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, PIPE);
    cr_assert_not_null(ast->left);
    cr_assert_not_null(ast->right);
    cr_assert_eq(ast->left->type, CONTENT);
    cr_assert_str_eq(ast->left->content[0], "ls");
    cr_assert_eq(ast->right->type, CONTENT);
    cr_assert_str_eq(ast->right->content[0], "cat");
    free_ast(ast);
    free_token_bundle(bundle);
    free_arr(env.ev_vars);
}

Test(parser_input, semicolon_creates_tree)
{
    env_t env = create_parser_env();
    token_bundle_t *bundle = lexer_input("ls ; pwd", &env);

    cr_assert_not_null(bundle);

    ast_node_t *ast = parser_input(bundle);

    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, SEMICOLON);
    cr_assert_not_null(ast->left);
    cr_assert_not_null(ast->right);
    free_ast(ast);
    free_token_bundle(bundle);
    free_arr(env.ev_vars);
}

Test(parser_input, redirect_right_creates_tree)
{
    env_t env = create_parser_env();
    token_bundle_t *bundle = lexer_input("echo hello > file", &env);

    cr_assert_not_null(bundle);

    ast_node_t *ast = parser_input(bundle);

    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, RED_RIGHT);
    cr_assert_not_null(ast->left);
    cr_assert_not_null(ast->right);
    free_ast(ast);
    free_token_bundle(bundle);
    free_arr(env.ev_vars);
}

Test(parser_input, redirect_left_creates_tree)
{
    env_t env = create_parser_env();
    token_bundle_t *bundle = lexer_input("cat < file", &env);

    cr_assert_not_null(bundle);

    ast_node_t *ast = parser_input(bundle);

    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, RED_LEFT);
    free_ast(ast);
    free_token_bundle(bundle);
    free_arr(env.ev_vars);
}

Test(parser_input, append_redirect_creates_tree)
{
    env_t env = create_parser_env();
    token_bundle_t *bundle = lexer_input("echo a >> file", &env);

    cr_assert_not_null(bundle);

    ast_node_t *ast = parser_input(bundle);

    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, RED_RIGHT_APP);
    free_ast(ast);
    free_token_bundle(bundle);
    free_arr(env.ev_vars);
}

Test(parser_input, heredoc_creates_tree)
{
    env_t env = create_parser_env();
    token_bundle_t *bundle = lexer_input("cat << EOF", &env);

    cr_assert_not_null(bundle);

    ast_node_t *ast = parser_input(bundle);

    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, HEREDOC);
    free_ast(ast);
    free_token_bundle(bundle);
    free_arr(env.ev_vars);
}

Test(parser_input, semicolon_lower_priority_than_pipe)
{
    env_t env = create_parser_env();
    token_bundle_t *bundle = lexer_input("ls | cat ; pwd", &env);

    cr_assert_not_null(bundle);

    ast_node_t *ast = parser_input(bundle);

    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, SEMICOLON);
    cr_assert_not_null(ast->left);
    cr_assert_eq(ast->left->type, PIPE);
    cr_assert_not_null(ast->right);
    cr_assert_eq(ast->right->type, CONTENT);
    free_ast(ast);
    free_token_bundle(bundle);
    free_arr(env.ev_vars);
}

Test(free_ast, null_does_not_crash)
{
    free_ast(NULL);
    cr_assert(1);
}

Test(free_token_bundle, null_does_not_crash)
{
    free_token_bundle(NULL);
    cr_assert(1);
}

Test(free_token_bundle, valid_bundle_is_freed)
{
    env_t env = create_parser_env();
    token_bundle_t *bundle = lexer_input("ls -la", &env);

    cr_assert_not_null(bundle);
    free_token_bundle(bundle);
    cr_assert(1);
    free_arr(env.ev_vars);
}
