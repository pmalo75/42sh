/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/
#include <stdlib.h>

#include "my_sh_def.h"
#include "global.h"
#include "my.h"

static int one_arg_condition(
    env_t *env, int idx, char *name)
{
    int len = 0;

    len = my_strlen(name) + 2;
    env->ev_vars[idx] = malloc(sizeof(char) * len);
    if (env->ev_vars[idx] == NULL)
        return (ERROR);
    if (my_strcpy(env->ev_vars[idx], name) == NULL)
        return (ERROR);
    if (my_strcat(env->ev_vars[idx], "=") == NULL)
        return (ERROR);
    return (SUCCESS);
}

static int fill_var(
    env_t *env, int idx, char *name, char *value)
{
    int len = 0;

    len = my_strlen(name) + 1;
    len += my_strlen(value) + 1;
    env->ev_vars[idx] = malloc(sizeof(char) * len);
    if (env->ev_vars[idx] == NULL)
        return (ERROR);
    if (my_strcpy(env->ev_vars[idx], name) == NULL)
        return (ERROR);
    if (my_strcat(env->ev_vars[idx], "=") == NULL)
        return (ERROR);
    if (my_strcat(env->ev_vars[idx], value) == NULL)
        return (ERROR);
    return (SUCCESS);
}

int replace_var(
    env_t *env, int idx, char *name, char *value)
{
    if (name == NULL)
        return (ERROR);
    free(env->ev_vars[idx]);
    if (name != NULL && value == NULL) {
        return (one_arg_condition(env, idx, name));
    }
    return (fill_var(env, idx, name, value));
}
