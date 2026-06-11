/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_is_file_ok
*/

#include <criterion/criterion.h>
#include "checker.h"
#include "my_sh_def.h"
#include "my.h"

Test(is_file_ok, finds_ls_in_path)
{
    env_t env = {0};
    char **vars = malloc(sizeof(char *) * 2);

    vars[0] = my_strdup("PATH=/usr/bin:/bin");
    vars[1] = NULL;
    env.ev_vars = vars;
    env.ev_path[0] = '\0';

    char **path_tab = get_path_values(&env);
    char *cmd[] = {"ls", NULL};

    int ret = is_file_ok(path_tab, &env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(path_tab);
    free_arr(env.ev_vars);
}

Test(is_file_ok, command_not_in_path)
{
    env_t env = {0};
    char **vars = malloc(sizeof(char *) * 2);

    vars[0] = my_strdup("PATH=/nonexistent");
    vars[1] = NULL;
    env.ev_vars = vars;
    env.ev_path[0] = '\0';

    char **path_tab = get_path_values(&env);
    char *cmd[] = {"nonexistent_command_xyz", NULL};

    int ret = is_file_ok(path_tab, &env, cmd);

    cr_assert_eq(ret, ERROR);
    free_arr(path_tab);
    free_arr(env.ev_vars);
}

Test(is_file_ok, finds_echo_in_path)
{
    env_t env = {0};
    char **vars = malloc(sizeof(char *) * 2);

    vars[0] = my_strdup("PATH=/usr/bin:/bin");
    vars[1] = NULL;
    env.ev_vars = vars;
    env.ev_path[0] = '\0';

    char **path_tab = get_path_values(&env);
    char *cmd[] = {"echo", NULL};

    int ret = is_file_ok(path_tab, &env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(path_tab);
    free_arr(env.ev_vars);
}
