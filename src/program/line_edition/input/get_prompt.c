/*
** EPITECH PROJECT, 2026
** mysh
** File description:
** mysh
*/

#include "my_sh_def.h"
#include "global.h"
#include "execute.h"
#include "my.h"

#include <stdio.h>

static int get_prompt_len(char *user, char *path)
{
    int len = 0;

    len += my_strlen(user);
    len += my_strlen(path);
    len += PR_EXTRA_LEN;
    return len;
}

char *get_prompt(env_t *env)
{
    char curr_path[PATH_MAX];
    char *user = parse_arr_element(env->ev_vars,"USER=", USER_PRE_LEN);
    int skip_home = get_home_len(env);
    char *prompt = NULL;
    int len = 0;

    if (getcwd(curr_path, sizeof(curr_path)) == NULL || !user)
        return strdup("> ");
    len = get_prompt_len(user, curr_path + skip_home);
    prompt = malloc(sizeof(char) * len);
    if (!prompt) {
        free(user);
        return NULL;
    }
    sprintf(prompt, "%s:~%s> ",
        user,
        curr_path + skip_home);
    free(user);
    return prompt;
}
