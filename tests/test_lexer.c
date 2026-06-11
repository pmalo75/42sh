/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_lexer
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "lexer.h"
#include "my.h"

static env_t create_empty_env(void)
{
    env_t env = {0};
    char **vars = malloc(sizeof(char *) * 2);

    vars[0] = my_strdup("PATH=/usr/bin:/bin");
    vars[1] = NULL;
    env.ev_vars = vars;
    env.ev_path[0] = '\0';
    return env;
}

Test(lexer_input, null_input_returns_null)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input(NULL, &env);

    cr_assert_null(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, single_space_returns_empty_bundle)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("ls", &env);

    cr_assert_not_null(result);
    cr_assert_geq(result->count, 1);
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, single_word)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("ls", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->count, 1);
    cr_assert_str_eq(result->tokens[0], "ls");
    cr_assert_eq(result->weights[0], 0);
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, multiple_words)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("ls -la /tmp", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->count, 3);
    cr_assert_str_eq(result->tokens[0], "ls");
    cr_assert_str_eq(result->tokens[1], "-la");
    cr_assert_str_eq(result->tokens[2], "/tmp");
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, pipe_operator)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("ls|grep foo", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->count, 4);
    cr_assert_str_eq(result->tokens[0], "ls");
    cr_assert_str_eq(result->tokens[1], "|");
    cr_assert_str_eq(result->tokens[2], "grep");
    cr_assert_str_eq(result->tokens[3], "foo");
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, pipe_with_spaces)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("ls | grep foo", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->count, 4);
    cr_assert_str_eq(result->tokens[0], "ls");
    cr_assert_str_eq(result->tokens[1], "|");
    cr_assert_str_eq(result->tokens[2], "grep");
    cr_assert_str_eq(result->tokens[3], "foo");
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, semicolon_operator)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("ls ; pwd", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->count, 3);
    cr_assert_str_eq(result->tokens[0], "ls");
    cr_assert_str_eq(result->tokens[1], ";");
    cr_assert_str_eq(result->tokens[2], "pwd");
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, right_redirect)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("echo hello > file", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->count, 4);
    cr_assert_str_eq(result->tokens[0], "echo");
    cr_assert_str_eq(result->tokens[1], "hello");
    cr_assert_str_eq(result->tokens[2], ">");
    cr_assert_str_eq(result->tokens[3], "file");
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, left_redirect)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("cat < file", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->count, 3);
    cr_assert_str_eq(result->tokens[0], "cat");
    cr_assert_str_eq(result->tokens[1], "<");
    cr_assert_str_eq(result->tokens[2], "file");
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, append_redirect)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("echo a >> file", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->count, 4);
    cr_assert_str_eq(result->tokens[0], "echo");
    cr_assert_str_eq(result->tokens[1], "a");
    cr_assert_str_eq(result->tokens[2], ">>");
    cr_assert_str_eq(result->tokens[3], "file");
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, heredoc_operator)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("cat << EOF", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->count, 3);
    cr_assert_str_eq(result->tokens[0], "cat");
    cr_assert_str_eq(result->tokens[1], "<<");
    cr_assert_str_eq(result->tokens[2], "EOF");
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, double_quoted_string)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("echo \"hello world\"", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->count, 2);
    cr_assert_str_eq(result->tokens[0], "echo");
    cr_assert_str_eq(result->tokens[1], "hello world");
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, tabs_as_separators)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("ls\t-la", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->count, 2);
    cr_assert_str_eq(result->tokens[0], "ls");
    cr_assert_str_eq(result->tokens[1], "-la");
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, multiple_operators)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("ls ; echo a | cat", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->count, 6);
    cr_assert_str_eq(result->tokens[0], "ls");
    cr_assert_str_eq(result->tokens[1], ";");
    cr_assert_str_eq(result->tokens[2], "echo");
    cr_assert_str_eq(result->tokens[3], "a");
    cr_assert_str_eq(result->tokens[4], "|");
    cr_assert_str_eq(result->tokens[5], "cat");
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, weight_content_is_zero)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("ls", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->weights[0], 0);
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, weight_semicolon_is_one)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("ls ; pwd", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->weights[1], 1);
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, weight_pipe_is_three)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("ls | cat", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->weights[1], 3);
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, weight_redirect_is_four)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("echo > file", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->weights[1], 4);
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, multiple_spaces_between_words)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("ls    -la", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->count, 2);
    cr_assert_str_eq(result->tokens[0], "ls");
    cr_assert_str_eq(result->tokens[1], "-la");
    free_token_bundle(result);
    free_arr(env.ev_vars);
}

Test(lexer_input, leading_and_trailing_spaces)
{
    env_t env = create_empty_env();

    token_bundle_t *result = lexer_input("  ls  ", &env);

    cr_assert_not_null(result);
    cr_assert_eq(result->count, 1);
    cr_assert_str_eq(result->tokens[0], "ls");
    free_token_bundle(result);
    free_arr(env.ev_vars);
}
