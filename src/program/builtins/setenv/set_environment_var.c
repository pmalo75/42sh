/*
** EPITECH PROJECT, 2026
** my_sh
** File description:
** my_sh
*/

#include "my_sh_def.h"
#include "my_builtins.h"
#include "my.h"


static int is_char_alpha(char c, int i)
{
    if (i > 0 && (c >= '0' && c <= '9'))
        return (0);
    if ((c >= 'a' && c <= 'z') || c == '_') {
        return (0);
    }
    if (c >= 'A' && c <= 'Z') {
        return (0);
    }
    if (i == 0 && (c >= '0' && c <= '9'))
        return (-1);
    return (-1);
}

static int is_valid_value(const char *s)
{
    if (s == NULL)
        return (-1);
    for (int i = 0; s[i]; i++) {
        if (is_char_alpha(s[i], i) == -1)
            return (-1);
    }
    return (0);
}

static int safe_guard(env_t *env, char **cmd)
{
    int n = 0;

    for (; cmd[n]; n++);
    if (n >= 4) {
        my_putsterr("setenv: Too many arguments.\n");
        return (-1);
    }
    if (n == 1) {
        my_env(env, cmd);
        return 2;
    }
    if (is_valid_value(cmd[1]) == -1) {
        my_putsterr("setenv: ");
        my_putsterr("Variable name must contain alphanumeric characters.\n");
        return (-1);
    }
    return (0);
}

int set_environment_var(env_t *env, char **cmd)
{
    int ret = safe_guard(env, cmd);

    if (ret == 2)
        return (SUCCESS);
    if (ret == -1)
        return (ERROR);
    return (my_setenv(env, cmd[1], cmd[2]));
}
