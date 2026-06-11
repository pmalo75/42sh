/*
** EPITECH PROJECT, 2026
** G-PSU-200-PAR-2-1-42sh-10
** File description:
** display_aliases
*/

#include "my_builtins.h"
#include "global.h"

#include <stdio.h>
#include <string.h>

static void reach_value(char **full_line)
{
    while (true) {
        if (**full_line == '=') {
            *(full_line) += 1;
            break;
        }
        (*full_line)++;
    }
}

static void display_value(const char *value)
{
    char *new_ptr = (char *)value;

    if (*new_ptr == '\"')
        new_ptr++;
    new_ptr[strcspn(new_ptr, "\"")] = '\0';
    printf("%s", new_ptr);
}

static void display_line(const char *line, const char *alias_to_display)
{
    char *save_ptr = NULL;
    char *token = strtok_r((char *)line, "=", &save_ptr);

    if (alias_to_display == NULL ||
        strncmp(token + 1, alias_to_display, strlen(alias_to_display)) == 0) {
        display_value(token);
        printf("\t");
        display_value(save_ptr);
        printf("\n");
        fflush(stdout);
    }
}

void display_aliases(env_t *env, const char *alias)
{
    char *alias_env_var = my_getenv(env, ALIAS_ENV_VAR);
    char *aliases_value_begin = NULL;
    char *token = NULL;

    if (alias_env_var == NULL)
        return;
    aliases_value_begin = alias_env_var;
    reach_value(&aliases_value_begin);
    token = strtok(aliases_value_begin, ";");
    while (token != NULL) {
        display_line(token, alias);
        token = strtok(NULL, ";");
    }
    free(alias_env_var);
}
