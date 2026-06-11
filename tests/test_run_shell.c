/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_run_shell
*/

#include <criterion/criterion.h>
#include "execute.h"
#include "my_sh_def.h"

Test(init_shell, null_envp_returns_success)
{
    int ret = init_shell(NULL);

    cr_assert_eq(ret, SUCCESS);
}
