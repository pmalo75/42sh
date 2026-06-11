/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <stdbool.h>

#include "my_sh_def.h"
#include "my_builtins.h"
#include "my.h"

static int safe_guard(char **cmd)
{
    int n = 0;

    for (; cmd[n]; n++);
    if (n == 1) {
        my_putsterr("unsetenv: Too few arguments.\n");
        return (-1);
    }
    return (0);
}

static int is_var_ok(const char *line, const char *name)
{
    int idx = 0;

    if (!line || !name)
        return (false);
    for (; name[idx]; idx++) {
        if (line[idx] == '\0' || line[idx] != name[idx]
            || line[idx] == '=')
            return (false);
    }
    if (line[idx] == '=')
        return (true);
    return (false);
}

static void delete_env_var(env_t *env, int idx)
{
    int n = idx;
    int i = idx;

    for (; env->ev_vars[n]; n++);
    if (env->ev_vars[idx])
        free(env->ev_vars[idx]);
    for (; i < n; i++) {
        env->ev_vars[i] = env->ev_vars[i + 1];
    }
    env->ev_vars[i] = NULL;
}

static void parse_env(env_t *env, char **cmd, int i)
{
    for (int j = 0; env->ev_vars[j]; j++) {
        if (is_var_ok(env->ev_vars[j], cmd[i])) {
            delete_env_var(env, j);
        }
    }
}

int my_unset(env_t *env, char **cmd)
{
    int ret = 0;

    ret = safe_guard(cmd);
    if (ret == -1)
        return (ERROR);
    for (int i = 1; cmd[i]; i++) {
        parse_env(env, cmd, i);
    }
    return (SUCCESS);
}
