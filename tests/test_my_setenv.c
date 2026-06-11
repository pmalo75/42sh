/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_my_setenv
*/

#include <criterion/criterion.h>
#include "my_builtins.h"
#include "my_sh_def.h"
#include "my.h"

Test(my_setenv, set_existing_var)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 3);

    dv[0] = my_strdup("PATH=/usr/bin");
    dv[1] = my_strdup("HOME=/home/user");
    dv[2] = NULL;
    env.ev_vars = dv;

    int ret = my_setenv(&env, "HOME", "/tmp");

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(my_setenv, set_new_var)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 2);

    dv[0] = my_strdup("PATH=/usr/bin");
    dv[1] = NULL;
    env.ev_vars = dv;

    int ret = my_setenv(&env, "NEWVAR", "value");

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(my_setenv, set_var_null_value)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 2);

    dv[0] = my_strdup("PATH=/usr/bin");
    dv[1] = NULL;
    env.ev_vars = dv;

    int ret = my_setenv(&env, "NEWVAR", NULL);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(my_setenv, replace_existing_null_value)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 2);

    dv[0] = my_strdup("HOME=/home/user");
    dv[1] = NULL;
    env.ev_vars = dv;

    int ret = my_setenv(&env, "HOME", NULL);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}
