/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Tests: Set Env Var
*/

#include <criterion/criterion.h>
#include "my_builtins.h"
#include "my_sh_def.h"
#include "my.h"

Test(set_environment_var, set_new_var_with_value)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 3);

    dynamic_vars[0] = my_strdup("OLDPWD=/tmp");
    dynamic_vars[1] = my_strdup("TAKE=");
    dynamic_vars[2] = NULL;
    env.ev_vars = dynamic_vars;
    env.ev_path[0] = '\0';

    char *cmd[] = {"setenv", "TAKE", "hello", NULL};
    int ret = set_environment_var(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(set_environment_var, set_existing_var)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 3);

    dynamic_vars[0] = my_strdup("OLDPWD=/tmp");
    dynamic_vars[1] = my_strdup("TAKE=");
    dynamic_vars[2] = NULL;
    env.ev_vars = dynamic_vars;
    env.ev_path[0] = '\0';

    char *cmd[] = {"setenv", "TAKE", NULL};
    int ret = set_environment_var(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(set_environment_var, invalid_var_name_starts_with_digit)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;
    env.ev_path[0] = '\0';

    char *cmd[] = {"setenv", "1TAK", NULL};
    int ret = set_environment_var(&env, cmd);

    cr_assert_eq(ret, ERROR);
    free_arr(env.ev_vars);
}

Test(set_environment_var, invalid_var_name_special_char)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;
    env.ev_path[0] = '\0';

    char *cmd[] = {"setenv", "TA@K", NULL};
    int ret = set_environment_var(&env, cmd);

    cr_assert_eq(ret, ERROR);
    free_arr(env.ev_vars);
}

Test(set_environment_var, too_many_arguments)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;
    env.ev_path[0] = '\0';

    char *cmd[] = {"setenv", "A", "B", "C", NULL};
    int ret = set_environment_var(&env, cmd);

    cr_assert_eq(ret, ERROR);
    free_arr(env.ev_vars);
}

Test(set_environment_var, no_args_displays_env)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 3);

    dynamic_vars[0] = my_strdup("OLDPWD=/tmp");
    dynamic_vars[1] = my_strdup("TAKE=val");
    dynamic_vars[2] = NULL;
    env.ev_vars = dynamic_vars;
    env.ev_path[0] = '\0';

    char *cmd[] = {"setenv", NULL};
    int ret = set_environment_var(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(set_environment_var, add_new_var_to_env)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;
    env.ev_path[0] = '\0';

    char *cmd[] = {"setenv", "NEWVAR", "newval", NULL};
    int ret = set_environment_var(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(set_environment_var, valid_underscore_name)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PATH=/usr/bin");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;
    env.ev_path[0] = '\0';

    char *cmd[] = {"setenv", "MY_VAR", "val", NULL};
    int ret = set_environment_var(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}
