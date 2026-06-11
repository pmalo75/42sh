/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_add_new_env_var
*/

#include <criterion/criterion.h>
#include "my_builtins.h"
#include "my_sh_def.h"
#include "my.h"

Test(add_new_var, with_name_and_value)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;

    int ret = add_new_var(&env, "MYVAR", "myvalue");

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(add_new_var, with_name_only_null_value)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;

    int ret = add_new_var(&env, "MYVAR", NULL);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(add_new_var, with_null_name_returns_error)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;

    int ret = add_new_var(&env, NULL, "value");

    cr_assert_eq(ret, ERROR);
    free_arr(env.ev_vars);
}

Test(add_new_var, adds_var_to_array)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;

    add_new_var(&env, "NEWVAR", "value");

    int count = 0;
    for (; env.ev_vars[count]; count++);

    cr_assert_eq(count, 2);
    free_arr(env.ev_vars);
}

Test(add_new_var, empty_value)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;

    int ret = add_new_var(&env, "MYVAR", "");

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}
