/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_move_home
*/

#include <criterion/criterion.h>
#include "my_builtins.h"
#include "my_sh_def.h"
#include "my.h"

Test(move_home, with_home_set_returns_success)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 3);

    dv[0] = my_strdup("HOME=/tmp");
    dv[1] = my_strdup("OLDPWD=/");
    dv[2] = NULL;
    env.ev_vars = dv;
    env.ev_path[0] = '\0';

    int ret = move_home(&env);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(move_home, no_home_var_returns_error)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 2);

    dv[0] = my_strdup("PATH=/usr/bin");
    dv[1] = NULL;
    env.ev_vars = dv;
    env.ev_path[0] = '\0';

    int ret = move_home(&env);

    cr_assert_eq(ret, ERROR);
    free_arr(env.ev_vars);
}

Test(move_home, empty_env_returns_error)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 1);

    dv[0] = NULL;
    env.ev_vars = dv;
    env.ev_path[0] = '\0';

    int ret = move_home(&env);

    cr_assert_eq(ret, ERROR);
    free(env.ev_vars);
}
