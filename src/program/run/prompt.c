/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "line_edition.h"
#include "global.h"
#include "my.h"

static int get_prompt_len(char *user, char *path)
{
    int len = 0;

    len += strlen(user);
    len += strlen(path);
    len += PR_EXTRA_LEN;
    return len;
}

static int get_home_len(env_t *env)
{
    char *home = NULL;
    int len = 0;

    home = parse_arr_element(env->ev_vars, "HOME=", 5);
    if (home == NULL)
        return 0;
    len = strlen(home);
    free(home);
    return len;
}

static char *create_prompt(char *user, char *path)
{
    char *prompt = NULL;
    int len = 0;

    len = get_prompt_len(user, path);
    prompt = malloc(sizeof(char) * len);
    if (!prompt)
        return NULL;
    sprintf(prompt, "\033[36m%s\033[0m:~\033[33m%s\033[0m> ", user, path);
    return prompt;
}

static char *manage_prompt(env_t *env)
{
    char curr_path[PATH_MAX];
    char *user = NULL;
    char *prompt = NULL;
    int skip_home = 0;

    user = parse_arr_element(env->ev_vars, "USER=", USER_PRE_LEN);
    skip_home = get_home_len(env);
    memset(curr_path, 0, sizeof(curr_path));
    if (getcwd(curr_path, sizeof(curr_path)) == NULL || !user)
        return strdup("> ");
    prompt = create_prompt(user, curr_path + skip_home);
    free(user);
    return prompt;
}

char *get_prompt(env_t *env)
{
    if (!isatty(0))
        return strdup("");
    if (*env->ev_vars == NULL)
        return strdup("> ");
    return manage_prompt(env);
}
