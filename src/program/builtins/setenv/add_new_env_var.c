/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include "my_sh_def.h"
#include "global.h"
#include "my.h"

static char *fill_var_with_content(char *name, char *value)
{
    int len = 0;
    char *buf = NULL;

    len = my_strlen(name) + 1;
    len += my_strlen(value) + 1;
    buf = my_calloc(len, sizeof(char));
    if (buf == NULL)
        return (NULL);
    if (my_strcpy(buf, name) == NULL)
        return (NULL);
    if (my_strcat(buf, "=") == NULL)
        return (NULL);
    if (my_strcat(buf, value) == NULL)
        return (NULL);
    return (buf);
}

static char *one_arg_condition(char *name)
{
    int len = 0;
    char *buf = NULL;

    len = my_strlen(name) + 2;
    buf = my_calloc(len, sizeof(char));
    if (buf == NULL)
        return (NULL);
    if (my_strcpy(buf, name) == NULL)
        return (NULL);
    if (my_strcat(buf, "=") == NULL)
        return (NULL);
    return (buf);
}

static char *create_var(char *name, char *value)
{
    char *buf = NULL;

    if (name == NULL)
        return (NULL);
    if (name != NULL && value == NULL) {
        buf = one_arg_condition(name);
        if (buf == NULL)
            return (NULL);
        return (buf);
    }
    return (fill_var_with_content(name, value));
}

int add_new_var(env_t *env, char *name, char *value)
{
    char *new_var = create_var(name, value);

    if (new_var == NULL)
        return (ERROR);
    env->ev_vars = realloc_2d_arr(env->ev_vars, new_var);
    if (env->ev_vars == NULL)
        return (ERROR);
    return (SUCCESS);
}
