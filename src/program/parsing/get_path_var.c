/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include "checker.h"
#include "global.h"
#include "my.h"

static char *get_path_var(env_t *env)
{
    char *var = parse_arr_element(env->ev_vars, "PATH=", 5);

    if (var == NULL) {
        return (NULL);
    }
    return (var);
}

char **get_path_values(env_t *env)
{
    char *path_line = get_path_var(env);
    char **path_tab = NULL;

    if (path_line == NULL) {
        path_line = my_strdup(DEFAULT_PATH);
        if (path_line == NULL)
            return (NULL);
    }
    path_tab = str_to_word_array(path_line, ":\n");
    free(path_line);
    if (path_tab == NULL) {
        return (NULL);
    }
    return (path_tab);
}
