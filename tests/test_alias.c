/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_alias
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my_builtins.h"
#include "my_sh_def.h"
#include "my.h"

static env_t create_alias_env(void)
{
    env_t env = {0};
    char **vars = malloc(sizeof(char *) * 2);

    vars[0] = my_strdup("PATH=/usr/bin:/bin");
    vars[1] = NULL;
    env.ev_vars = vars;
    env.ev_path[0] = '\0';
    return env;
}

Test(alias, no_args_displays_aliases)
{
    env_t env = create_alias_env();
    char *cmd[] = {"alias", NULL};

    int ret = alias(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(alias, one_arg_displays_specific)
{
    env_t env = create_alias_env();
    char *cmd[] = {"alias", "ll", NULL};

    int ret = alias(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(alias, create_alias_returns_success)
{
    env_t env = create_alias_env();
    char *cmd[] = {"alias", "ll", "ls", "-la", NULL};

    int ret = alias(&env, cmd);

    cr_assert_eq(ret, SUCCESS);
    free_arr(env.ev_vars);
}

Test(alias, create_two_aliases)
{
    env_t env = create_alias_env();
    char *cmd1[] = {"alias", "ll", "ls", "-la", NULL};
    char *cmd2[] = {"alias", "la", "ls", "-a", NULL};

    int ret1 = alias(&env, cmd1);
    int ret2 = alias(&env, cmd2);

    cr_assert_eq(ret1, SUCCESS);
    cr_assert_eq(ret2, SUCCESS);
    free_arr(env.ev_vars);
}

Test(my_getenv, found_existing_var)
{
    env_t env = create_alias_env();

    char *result = my_getenv(&env, "PATH");

    cr_assert_not_null(result);
    free(result);
    free_arr(env.ev_vars);
}

Test(my_getenv, not_found_returns_null)
{
    env_t env = create_alias_env();

    char *result = my_getenv(&env, "NONEXISTENT");

    cr_assert_null(result);
    free_arr(env.ev_vars);
}

Test(my_getenv, found_var_contains_key)
{
    env_t env = {0};
    char **vars = malloc(sizeof(char *) * 3);

    vars[0] = my_strdup("HOME=/home/user");
    vars[1] = my_strdup("PATH=/usr/bin");
    vars[2] = NULL;
    env.ev_vars = vars;

    char *result = my_getenv(&env, "HOME");

    cr_assert_not_null(result);
    cr_assert(strstr(result, "HOME") != NULL);
    free(result);
    free_arr(env.ev_vars);
}
