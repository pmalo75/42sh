/*
** EPITECH PROJECT, 2026
** my_sh
** File description:
** my_sh
*/

#include <stdbool.h>

#include "my_builtins.h"

static bool is_var_exist(const char *line, const char *name)
{
    int idx = 0;

    if (line == NULL || name == NULL)
        return false;
    for (; name[idx]; idx++) {
        if (line[idx] == '\0' || line[idx] != name[idx])
            return false;
    }
    if (line[idx] == '=')
        return true;
    return false;
}

int my_setenv(env_t *env, char *name, char *value)
{
    for (size_t i = 0; env->ev_vars[i]; i++) {
        if (is_var_exist(env->ev_vars[i], name) == true) {
            return replace_var(env, i, name, value);
        }
    }
    return add_new_var(env, name, value);
}
