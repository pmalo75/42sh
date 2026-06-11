/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_get_path_var
*/

#include <criterion/criterion.h>
#include "checker.h"
#include "my.h"

Test(get_path_values, with_path_set)
{
    env_t env = {0};
    char **vars = malloc(sizeof(char *) * 2);

    vars[0] = my_strdup("PATH=/usr/bin:/bin:/sbin");
    vars[1] = NULL;
    env.ev_vars = vars;
    env.ev_path[0] = '\0';

    char **result = get_path_values(&env);

    cr_assert_not_null(result);
    cr_assert_str_eq(result[0], "/usr/bin");
    cr_assert_str_eq(result[1], "/bin");
    cr_assert_str_eq(result[2], "/sbin");
    free_arr(result);
    free_arr(env.ev_vars);
}

Test(get_path_values, without_path_uses_default)
{
    env_t env = {0};
    char **vars = malloc(sizeof(char *) * 2);

    vars[0] = my_strdup("HOME=/tmp");
    vars[1] = NULL;
    env.ev_vars = vars;
    env.ev_path[0] = '\0';

    char **result = get_path_values(&env);

    cr_assert_not_null(result);
    free_arr(result);
    free_arr(env.ev_vars);
}

Test(get_path_values, single_path_entry)
{
    env_t env = {0};
    char **vars = malloc(sizeof(char *) * 2);

    vars[0] = my_strdup("PATH=/usr/bin");
    vars[1] = NULL;
    env.ev_vars = vars;
    env.ev_path[0] = '\0';

    char **result = get_path_values(&env);

    cr_assert_not_null(result);
    cr_assert_str_eq(result[0], "/usr/bin");
    free_arr(result);
    free_arr(env.ev_vars);
}
