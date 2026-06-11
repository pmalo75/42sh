/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "global.h"
#include "my_sh_def.h"

static int print_usage(void)
{
    printf("Usage: unset [key] ...\n");
    return FUNC_SUCCESS;
}

static int check_if_exist(env_t *env, char *key)
{
    size_t len = strlen(key);
    char next_char = '\0';

    for (size_t i = 0; env->local_vars[i] != NULL; i++) {
        if (strncmp(env->local_vars[i], key, len) != 0)
            continue;
        next_char = env->local_vars[i][len];
        if (next_char == ' ' || next_char == '\0')
            return i;
    }
    return -1;
}

static void del_element(env_t *env, char *key)
{
    int row_idx = check_if_exist(env, key);

    if (row_idx == -1)
        return;
    free(env->local_vars[row_idx]);
    for (size_t i = row_idx; env->local_vars[i] != NULL; i++) {
        env->local_vars[i] = env->local_vars[i + 1];
    }
}

int unset_builtin(env_t *env, char **cmd)
{
    size_t n = 0;

    for (; cmd[n] != NULL; n++);
    if (n == 1)
        return print_usage();
    for (size_t i = 1; cmd[i] != NULL; i++) {
        del_element(env, cmd[i]);
    }
    return FUNC_SUCCESS;
}
