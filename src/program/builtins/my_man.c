#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "my_sh_def.h"
#include "my_builtins.h"


int my_man(env_t *env, char **cmd)
{
    pid_t pid;
    int status;

    (void)env;

    pid = fork();
    if (pid < 0)
        return (ERROR);

    if (pid == 0) {
        if (cmd[1] && !cmd[2] && strcmp(cmd[1], "42sh") == 0)
            execlp("man", "man", "./doc/42.1", NULL);
        else
            execvp("man", cmd);
        exit(84);
    }

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (ERROR);
}
