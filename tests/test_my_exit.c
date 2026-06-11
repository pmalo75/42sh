/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_my_exit
*/

#include <criterion/criterion.h>
#include "my_builtins.h"
#include "my_sh_def.h"
#include "my.h"

Test(my_exit, exit_no_args_returns_success)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;
    env.is_running = true;

    char *cmd[] = {"exit", NULL};
    int ret = my_exit(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    cr_assert_eq(env.is_running, false);
    free_arr(env.ev_vars);
}

Test(my_exit, exit_with_valid_number)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;
    env.is_running = true;

    char *cmd[] = {"exit", "42", NULL};
    int ret = my_exit(&env, cmd);

    cr_assert_eq(ret, 42);
    cr_assert_eq(env.is_running, false);
    free_arr(env.ev_vars);
}

Test(my_exit, exit_with_zero)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;
    env.is_running = true;

    char *cmd[] = {"exit", "0", NULL};
    int ret = my_exit(&env, cmd);

    cr_assert_eq(ret, 0);
    cr_assert_eq(env.is_running, false);
    free_arr(env.ev_vars);
}

Test(my_exit, exit_with_non_numeric_returns_error)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;
    env.is_running = true;

    char *cmd[] = {"exit", "abc", NULL};
    int ret = my_exit(&env, cmd);

    cr_assert_eq(ret, ERROR);
    free_arr(env.ev_vars);
}

Test(my_exit, exit_too_many_args_returns_error)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;
    env.is_running = true;

    char *cmd[] = {"exit", "1", "2", NULL};
    int ret = my_exit(&env, cmd);

    cr_assert_eq(ret, ERROR);
    free_arr(env.ev_vars);
}

Test(my_exit, exit_sets_is_running_false)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;
    env.is_running = true;

    char *cmd[] = {"exit", NULL};
    my_exit(&env, cmd);

    cr_assert_eq(env.is_running, false);
    free_arr(env.ev_vars);
}
