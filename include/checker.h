/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#ifndef CHECKER_H_
    #define CHECKER_H_
    #include "global.h"

    #define CTRL_D NULL
    #define DEFAULT_PATH "/usr/sbin:/usr/bin:/sbin:/bin"

//program >> parsing
int get_cmd_path(env_t *env, char **cmd);
char **get_path_values(env_t *env);
int is_file_ok(char **path_tab, env_t *env, char **cmd);

#endif /* !CHECKER_H_ */
