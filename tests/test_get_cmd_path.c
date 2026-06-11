/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_get_cmd_path
*/

#include <criterion/criterion.h>
#include "checker.h"
#include "my_sh_def.h"
#include "my.h"

Test(get_cmd_path, null_env_returns_error)
{
    int ret = get_cmd_path(NULL, NULL);

    cr_assert_eq(ret, ERROR);
}

Test(get_cmd_path, absolute_path_ls)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 2);

    dv[0] = my_strdup("PATH=/usr/bin:/bin");
    dv[1] = NULL;
    env.ev_vars = dv;
    env.ev_path[0] = '\0';

    char *cmd[] = {"/bin/ls", NULL};
    int ret = get_cmd_path(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(get_cmd_path, command_in_path)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 2);

    dv[0] = my_strdup("PATH=/usr/bin:/bin");
    dv[1] = NULL;
    env.ev_vars = dv;
    env.ev_path[0] = '\0';

    char *cmd[] = {"ls", NULL};
    int ret = get_cmd_path(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(get_cmd_path, nonexistent_command)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 2);

    dv[0] = my_strdup("PATH=/usr/bin:/bin");
    dv[1] = NULL;
    env.ev_vars = dv;
    env.ev_path[0] = '\0';

    char *cmd[] = {"nonexistent_cmd_xyz", NULL};
    int ret = get_cmd_path(&env, cmd);

    cr_assert_eq(ret, ERROR);
    free_arr(env.ev_vars);
}

Test(get_cmd_path, absolute_path_nonexistent)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 2);

    dv[0] = my_strdup("PATH=/usr/bin:/bin");
    dv[1] = NULL;
    env.ev_vars = dv;
    env.ev_path[0] = '\0';

    char *cmd[] = {"/nonexistent/path/cmd", NULL};
    int ret = get_cmd_path(&env, cmd);

    cr_assert_eq(ret, ERROR);
    free_arr(env.ev_vars);
}

Test(get_cmd_path, no_path_var_with_absolute_path)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 2);

    dv[0] = my_strdup("HOME=/tmp");
    dv[1] = NULL;
    env.ev_vars = dv;
    env.ev_path[0] = '\0';

    char *cmd[] = {"ls", NULL};
    int ret = get_cmd_path(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(get_cmd_path, directory_as_cmd_returns_error)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 2);

    dv[0] = my_strdup("PATH=/usr/bin:/bin");
    dv[1] = NULL;
    env.ev_vars = dv;
    env.ev_path[0] = '\0';

    char *cmd[] = {"/tmp", NULL};
    int ret = get_cmd_path(&env, cmd);

    cr_assert_eq(ret, ERROR);
    free_arr(env.ev_vars);
}
