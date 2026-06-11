/*
** EPITECH PROJECT, 2026
** G-PSU-200-PAR-2-1-42sh-10
** File description:
** replace_aliases
*/

#include <string.h>
#include <stdio.h>

#include "global.h"
#include "my_builtins.h"
#include "lexer.h"

static bool token_is_alias(char *token, char *alias_line)
{
    char *alias_line_dup = strdup(alias_line);
    char *alias_line_value = NULL;
    bool result = false;
    char *saveptr = NULL;

    if (alias_line_dup == NULL)
        return false;
    alias_line_value = strtok_r(alias_line_dup, "=", &saveptr);
    alias_line_value++;
    alias_line_value[strlen(alias_line_value) - 1] = '\0';
    result = strcmp(token, alias_line_value) == 0;
    free(alias_line_dup);
    return result;
}

static void iterate_on_aliases(char *aliases,
    token_bundle_t *tokens_bundle,
    size_t tokens_index)
{
    char ***tokens = &tokens_bundle->tokens;
    char *alias = strtok(aliases, ";");

    while (alias != NULL) {
        if (token_is_alias((*tokens)[tokens_index], alias)) {
            replace_value(tokens_bundle,
                tokens_index,
                alias,
                &tokens_bundle->count);
            break;
        }
        alias = strtok(NULL, ";");
    }
}

void replace_aliases(token_bundle_t *tokens,
    env_t *env,
    size_t recursion_count)
{
    char *alias_var = NULL;
    char *value_ptr = NULL;
    char *value_dup = NULL;

    if (recursion_count > MAX_ALIAS_RECURSION ||
        tokens->tokens[0] == NULL || strcmp(tokens->tokens[0], "alias") == 0)
        return;
    alias_var = my_getenv(env, ALIAS_ENV_VAR);
    if (alias_var == NULL)
        return;
    value_ptr = alias_var + strcspn(alias_var, "=") + 1;
    for (size_t i = 0; tokens->tokens[i] != NULL; i++) {
        value_dup = strdup(value_ptr);
        if (value_dup == NULL)
            break;
        iterate_on_aliases(value_dup, tokens, i);
        free(value_dup);
    }
    free(alias_var);
    replace_aliases(tokens, env, recursion_count + 1);
}
