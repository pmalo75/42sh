/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_replace_var
*/

#include <criterion/criterion.h>
#include "my_builtins.h"
#include "my_sh_def.h"
#include "my.h"

Test(replace_var, with_name_and_value)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 3);

    dynamic_vars[0] = my_strdup("OLDPWD=/tmp");
    dynamic_vars[1] = my_strdup("TAKE=");
    dynamic_vars[2] = NULL;
    env.ev_vars = dynamic_vars;

    int ret = replace_var(&env, 0, "OLDPWD", "newvalue");

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(replace_var, with_null_name_returns_error)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("TEST=val");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;

    int ret = replace_var(&env, 0, NULL, NULL);

    cr_assert_eq(ret, ERROR);
    free_arr(env.ev_vars);
}

Test(replace_var, with_name_null_value)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("OLDPWD=/tmp");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;

    int ret = replace_var(&env, 0, "OLDPWD", NULL);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(replace_var, replaces_second_element)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 3);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = my_strdup("HOME=/home/user");
    dynamic_vars[2] = NULL;
    env.ev_vars = dynamic_vars;

    int ret = replace_var(&env, 1, "HOME", "/tmp");

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}
