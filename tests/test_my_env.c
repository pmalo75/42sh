/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_my_env
*/

#include <criterion/criterion.h>
#include "my_builtins.h"
#include "my_sh_def.h"
#include "my.h"

Test(my_env, displays_env_returns_success)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 3);

    dynamic_vars[0] = my_strdup("OLDPWD=/tmp");
    dynamic_vars[1] = my_strdup("TAKE=value");
    dynamic_vars[2] = NULL;
    env.ev_vars = dynamic_vars;

    char *cmd[] = {"env", NULL};
    int ret = my_env(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(my_env, with_args_returns_error)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;

    char *cmd[] = {"env", "extra", NULL};
    int ret = my_env(&env, cmd);

    cr_assert_eq(ret, ERROR);
    free_arr(env.ev_vars);
}

Test(my_env, single_var_env)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("HOME=/tmp");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;

    char *cmd[] = {"env", NULL};
    int ret = my_env(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}
