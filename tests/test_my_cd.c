/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_my_cd
*/

#include <criterion/criterion.h>
#include "my_builtins.h"
#include "my_sh_def.h"
#include "my.h"

Test(my_cd, cd_to_tmp_returns_success)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 3);

    dynamic_vars[0] = my_strdup("OLDPWD=/tmp");
    dynamic_vars[1] = my_strdup("PWD=/tmp");
    dynamic_vars[2] = NULL;
    env.ev_vars = dynamic_vars;
    env.ev_path[0] = '\0';

    char *cmd[] = {"cd", "/tmp", NULL};
    int ret = my_cd(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(my_cd, too_many_args_returns_error)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = NULL;
    env.ev_vars = dynamic_vars;
    env.ev_path[0] = '\0';

    char *cmd[] = {"cd", "a", "b", NULL};
    int ret = my_cd(&env, cmd);

    cr_assert_eq(ret, ERROR);
    free(env.ev_vars);
}

Test(my_cd, cd_tilde_triggers_move_home)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 3);

    dynamic_vars[0] = my_strdup("HOME=/tmp");
    dynamic_vars[1] = my_strdup("OLDPWD=/");
    dynamic_vars[2] = NULL;
    env.ev_vars = dynamic_vars;
    env.ev_path[0] = '\0';

    char *cmd[] = {"cd", "~", NULL};
    int ret = my_cd(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(my_cd, cd_dash_triggers_move_old_dir)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 3);

    dynamic_vars[0] = my_strdup("OLDPWD=/tmp");
    dynamic_vars[1] = my_strdup("PWD=/");
    dynamic_vars[2] = NULL;
    env.ev_vars = dynamic_vars;
    env.ev_path[0] = '\0';

    char *cmd[] = {"cd", "-", NULL};
    int ret = my_cd(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(my_cd, cd_no_args_goes_home)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 3);

    dynamic_vars[0] = my_strdup("HOME=/tmp");
    dynamic_vars[1] = my_strdup("OLDPWD=/");
    dynamic_vars[2] = NULL;
    env.ev_vars = dynamic_vars;
    env.ev_path[0] = '\0';

    char *cmd[] = {"cd", NULL};
    int ret = my_cd(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(my_cd, cd_nonexistent_dir_returns_error)
{
    env_t env = {0};
    char **dynamic_vars = malloc(sizeof(char *) * 2);

    dynamic_vars[0] = my_strdup("PWD=/tmp");
    dynamic_vars[1] = NULL;
    env.ev_vars = dynamic_vars;
    env.ev_path[0] = '\0';

    char *cmd[] = {"cd", "/nonexistent_dir_xyz_42sh", NULL};
    int ret = my_cd(&env, cmd);

    cr_assert_eq(ret, ERROR);
    free_arr(env.ev_vars);
}
