/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "my_sh_def.h"
#include "global.h"

static int print_local(env_t *env)
{
    for (size_t i = 0; env->local_vars[i] != NULL; i++) {
        printf("%s\n", env->local_vars[i]);
    }
    return FUNC_SUCCESS;
}

static int print_usage(void)
{
    printf(
        "Usage: set [--help]\n"
        "set arguments should be always paired.\n"
        "set <name> <value>\n"
        "if no value needs to be set: set <name> ~\n"
    );
    return FUNC_SUCCESS;
}

static size_t count_2d_arr(char **arr)
{
    size_t len = 0;

    while (arr[len] != NULL)
        len++;
    return len;
}

static int add_to_arr(env_t *env, char *key, char *value)
{
    size_t len_arr = count_2d_arr(env->local_vars);
    char **temp = realloc(env->local_vars, (len_arr + 2) * sizeof(char *));

    if (temp == NULL)
        return FUNC_FAIL;
    env->local_vars = temp;
    if (strcmp(value, "~") == 0) {
        if (asprintf(&env->local_vars[len_arr], "%s", key) == -1)
            return FUNC_FAIL;
        env->local_vars[len_arr + 1] = NULL;
        return FUNC_SUCCESS;
    }
    if (asprintf(&env->local_vars[len_arr], "%s ~ %s", key, value) == -1)
        return FUNC_FAIL;
    env->local_vars[len_arr + 1] = NULL;
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

static int modify_element(env_t *env, char *key, char *value)
{
    int row_idx = check_if_exist(env, key);
    char *new_str = NULL;

    if (row_idx == -1) {
        if (add_to_arr(env, key, value) == FUNC_FAIL)
            return FUNC_FAIL;
        return FUNC_SUCCESS;
    }
    if (strcmp(value, "~") == 0) {
        if (asprintf(&new_str, "%s", key) == -1)
            return FUNC_FAIL;
    } else {
        if (asprintf(&new_str, "%s ~ %s", key, value) == -1)
            return FUNC_FAIL;
    }
    free(env->local_vars[row_idx]);
    env->local_vars[row_idx] = new_str;
    return FUNC_SUCCESS;
}

static int set_local_var(env_t *env, char **cmd)
{
    for (size_t i = 1; cmd[i] != NULL; i += 2) {
        if (modify_element(env, cmd[i], cmd[i + 1]) == FUNC_FAIL)
            return FUNC_FAIL;
    }
    return FUNC_SUCCESS;
}

int set_builtin(env_t *env, char **cmd)
{
    size_t n = count_2d_arr(cmd);

    if ((n - 1) % 2 != 0) {
        dprintf(2, "Format error: Check -h or --help\n");
        return FUNC_FAIL;
    }
    if (n == 1)
        return print_local(env);
    if (n == 2 &&
        (strncmp(cmd[1], "--help", 7) == 0 || strncmp(cmd[1], "-h", 3) == 0))
        return print_usage();
    return set_local_var(env, cmd);
}
