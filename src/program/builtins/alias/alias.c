/*
** EPITECH PROJECT, 2026
** G-PSU-200-PAR-2-1-42sh-10
** File description:
** alias
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "global.h"
#include "my_sh_def.h"
#include "my_builtins.h"

static size_t get_size_of_tokens(const char **tokens)
{
    size_t count = 0;

    for (size_t i = 2; tokens[i] != NULL; i++) {
        count += strlen(tokens[i]);
        count += strlen(" ");
    }
    return count;
}

static char *create_new_entry(char *alias, const char **target)
{
    char *new_str = calloc(strlen(alias) + get_size_of_tokens(target) +
        ALIAS_ENV_VAR_EXTRA_LEN + 1, sizeof(char));

    if (new_str == NULL)
        return NULL;
    new_str[0] = '\0';
    strcat(new_str, "\"");
    strcat(new_str, alias);
    strcat(new_str, "\"");
    strcat(new_str, "=");
    strcat(new_str, "\"");
    for (size_t i = 2; target[i] != NULL; i++) {
        strcat(new_str, target[i]);
        strcat(new_str, " ");
    }
    strcat(new_str, "\"");
    return new_str;
}

static char *add_entry(char *new_entry, char *old_env)
{
    char *new_str = calloc(strlen(new_entry) + strlen(old_env) +
        strlen(";") + 1, sizeof(char));

    if (new_str == NULL)
        return NULL;
    new_str[0] = '\0';
    strcat(new_str, old_env);
    strcat(new_str, ";");
    strcat(new_str, new_entry);
    return new_str;
}

char *my_getenv(env_t *env, char *key)
{
    for (size_t i = 0; env->ev_vars[i] != NULL; i++) {
        if (strncmp(env->ev_vars[i], key,
                strcspn(env->ev_vars[i], "=")) == 0)
            return strdup(env->ev_vars[i]);
    }
    return NULL;
}

static int add_alias_in_env(env_t *env, char *alias, const char **target)
{
    char *new_entry = create_new_entry(alias, target);
    char *temp = NULL;
    char *alias_env_line = my_getenv(env, ALIAS_ENV_VAR);

    if (new_entry == NULL)
        return ERROR;
    if (alias_env_line == NULL)
        my_setenv(env, ALIAS_ENV_VAR, new_entry);
    else {
        temp = add_entry(new_entry, alias_env_line);
        my_setenv(env, ALIAS_ENV_VAR, temp + strcspn(temp, "=") + 1);
        free(temp);
    }
    free(new_entry);
    free(alias_env_line);
    return SUCCESS;
}

int alias(env_t *env, char **cmd)
{
    if (cmd[1] == NULL) {
        display_aliases(env, NULL);
        return SUCCESS;
    }
    if (cmd[2] == NULL) {
        display_aliases(env, cmd[1]);
        return SUCCESS;
    }
    return add_alias_in_env(env, cmd[1], (const char **)cmd);
}
