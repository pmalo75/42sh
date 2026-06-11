/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_my_unset
*/

#include <criterion/criterion.h>
#include "my_builtins.h"
#include "my_sh_def.h"
#include "my.h"

Test(my_unset, unset_existing_var)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 3);

    dv[0] = my_strdup("OLDPWD=/tmp");
    dv[1] = my_strdup("TAKE=");
    dv[2] = NULL;
    env.ev_vars = dv;

    char *cmd[] = {"unsetenv", "TAKE", NULL};
    int ret = my_unset(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(my_unset, too_few_args)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 2);

    dv[0] = my_strdup("PATH=/usr/bin");
    dv[1] = NULL;
    env.ev_vars = dv;

    char *cmd[] = {"unsetenv", NULL};
    int ret = my_unset(&env, cmd);

    cr_assert_eq(ret, ERROR);
    free_arr(env.ev_vars);
}

Test(my_unset, unset_nonexistent_var)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 2);

    dv[0] = my_strdup("PATH=/usr/bin");
    dv[1] = NULL;
    env.ev_vars = dv;

    char *cmd[] = {"unsetenv", "NONEXISTENT", NULL};
    int ret = my_unset(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(my_unset, unset_multiple_vars)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 4);

    dv[0] = my_strdup("A=1");
    dv[1] = my_strdup("B=2");
    dv[2] = my_strdup("C=3");
    dv[3] = NULL;
    env.ev_vars = dv;

    char *cmd[] = {"unsetenv", "A", "C", NULL};
    int ret = my_unset(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}
