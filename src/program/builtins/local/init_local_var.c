/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <sys/types.h>
#include <pwd.h>

#include "my_sh_def.h"
#include "global.h"

static int get_current_dir(env_t *env)
{
    char *cwd = getcwd(NULL, 0);

    if (cwd == NULL)
        return (FUNC_FAIL);
    env->local_vars[0] = malloc(strlen(cwd) + 7);
    if (env->local_vars[0] == NULL) {
        free(cwd);
        return (FUNC_FAIL);
    }
    if (snprintf(env->local_vars[0],
            strlen(cwd) + 7, "cwd ~ %s", cwd) < 0) {
        free(cwd);
        return (FUNC_FAIL);
    }
    free(cwd);
    return (FUNC_SUCCESS);
}

static int get_username(env_t *env, uid_t uid)
{
    struct passwd *pws = getpwuid(uid);

    if (pws == NULL)
        return (FUNC_FAIL);
    env->local_vars[2] = malloc(strlen(pws->pw_name) + 8);
    if (env->local_vars[2] == NULL) {
        perror("malloc");
        return (FUNC_FAIL);
    }
    if (snprintf(env->local_vars[2],
            strlen(pws->pw_name) + 8, "user ~ %s", pws->pw_name) < 0) {
        return (FUNC_FAIL);
    }
    return (FUNC_SUCCESS);
}

static int get_user_info(env_t *env)
{
    uid_t uid = getuid();
    int len = 0;

    len = snprintf(NULL, 0, "%d", uid);
    if (len < 0)
        return (FUNC_FAIL);
    env->local_vars[1] = malloc(len + 7);
    if (env->local_vars[1] == NULL) {
        perror("malloc");
        return (FUNC_FAIL);
    }
    if (snprintf(env->local_vars[1], len + 7, "uid ~ %d", uid) < 0)
        return (FUNC_FAIL);
    if (get_username(env, uid) == FUNC_FAIL)
        return (FUNC_FAIL);
    return (FUNC_SUCCESS);
}

static int fill_local_var(env_t *env)
{
    if (get_current_dir(env) == FUNC_FAIL)
        return (FUNC_FAIL);
    if (get_user_info(env) == FUNC_FAIL)
        return (FUNC_FAIL);
    return (FUNC_SUCCESS);
}

int init_local_var(env_t *env)
{
    env->local_vars = calloc(4, sizeof(char *));
    if (env->local_vars == NULL)
        return (FUNC_FAIL);
    if (fill_local_var(env) == FUNC_FAIL)
        return (FUNC_FAIL);
    return (FUNC_SUCCESS);
}
