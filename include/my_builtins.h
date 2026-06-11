/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#ifndef BUILTINS_H_
    #define BUILTINS_H_
    #include "global.h"
    #define ALIAS_ENV_VAR "ALIAS"
    #define ALIAS_ENV_VAR_EXTRA_LEN strlen("\"\"\"\"=")
    #define MAX_ALIAS_RECURSION 40
    #define STRING_EQUAL 0

// Credits
const static char GROUPDIR[] = "src/resources/group";
const static char PERSOGROUP[] = "src/resources/group/users";
const static char TEAM_MEMBERS_ASCII[] = "our_team.42";
const static char NFO[] = "42sh.nfo";
typedef struct users_s {
    char *name;
    char *filename;
    char *email;
    char *description;
} users_t;

static const users_t users[] = {
    {"Thibault", "portrait_3.42", "thibault.morez@epitech.eu",
        "Perfection incarnée depuis toujours."},
    {"Thomas", "portrait_4.42", "thomas.rigault@epitech.eu",
        "Kong lover"},
    {"Pierre-Malo", "portrait_2.42", "pierre-malo.bernabeu@epitech.eu",
        "La débauche"},
    {"Eduardo", "portrait_1.42", "eduardo.almeida@epitech.eu",
        "Edouardo"},
    {"Matthias", "portrait_5.42", "matthias.germain@epitech.eu",
        "#giveUP"},
    {NULL, NULL, NULL, NULL}
};

//program >> builtins >> cd
int my_cd(env_t *env, char **cmd);

int move_home(env_t *env);
int move_old_dir(env_t *env);
int move_directory(env_t *env, char **cmd);
//program >> builtins >> setenv
int set_environment_var(env_t *env, char **cmd);

int my_setenv(env_t *env, char *name, char *value);
int replace_var(
    env_t *env, int idx, char *name, char *value);
int add_new_var(env_t *env, char *name, char *value);
void display_aliases(env_t *env, const char *alias);
//program >> builtins
int my_env(env_t *env, char **cmd);
int my_exit(env_t *env, char **cmd);
int my_unset(env_t *env, char **cmd);
int alias(env_t *env, char **cmd);
int my_history(env_t *env, char **args);
int set_builtin(env_t *env, char **cmd);
int unset_builtin(env_t *env, char **cmd);

int jobs(env_t *env, char **cmd);
int bg_builtin(env_t *env, char **cmd);
int fg_builtin(env_t *env, char **cmd);

int credits(env_t *env, char **cmd);

int mediaplayer(env_t *env, char **cmd);

typedef struct builtin_s {
    char *name;
    int (*func)(struct env_s *env, char **cmd);
} builtin_t;

static const builtin_t BUILTINS[] = {
    {"cd", my_cd},
    {"env", my_env},
    {"setenv", set_environment_var},
    {"unsetenv", my_unset},
    {"exit", my_exit},
    {"alias", alias},
    {"set", set_builtin},
    {"unset", unset_builtin},
    {"history", my_history},
    {"jobs", jobs},
    {"bg", bg_builtin},
    {"fg", fg_builtin},
    {"credits", credits},
    {"mediaplayer", mediaplayer},
    {NULL, NULL}
};

#endif /* !BUILTINS_H_ */
