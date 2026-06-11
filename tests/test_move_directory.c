/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_move_directory
*/

#include <criterion/criterion.h>
#include "my_builtins.h"
#include "my_sh_def.h"
#include "my.h"

Test(move_directory, to_tmp_returns_success)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 3);

    dv[0] = my_strdup("OLDPWD=/");
    dv[1] = my_strdup("PWD=/tmp");
    dv[2] = NULL;
    env.ev_vars = dv;
    env.ev_path[0] = '\0';

    char *cmd[] = {"cd", "/tmp", NULL};
    int ret = move_directory(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(move_directory, nonexistent_dir_returns_error)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 2);

    dv[0] = my_strdup("PWD=/tmp");
    dv[1] = NULL;
    env.ev_vars = dv;
    env.ev_path[0] = '\0';

    char *cmd[] = {"cd", "/nonexistent_xyz_42", NULL};
    int ret = move_directory(&env, cmd);

    cr_assert_eq(ret, ERROR);
    free_arr(env.ev_vars);
}

Test(move_directory, file_not_dir_returns_error)
{
    env_t env = {0};
    char **dv = malloc(sizeof(char *) * 2);

    dv[0] = my_strdup("PWD=/tmp");
    dv[1] = NULL;
    env.ev_vars = dv;
    env.ev_path[0] = '\0';

    char *cmd[] = {"cd", "/bin/ls", NULL};
    int ret = move_directory(&env, cmd);

    cr_assert_eq(ret, ERROR);
    free_arr(env.ev_vars);
}
