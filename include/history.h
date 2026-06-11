/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#ifndef HISTORY_H_
    #define HISTORY_H_

    #include "parser.h"
    #include "global.h"

char *get_history_path(void);
void save_history(char *cmd);
time_t get_timestamp(void);
#endif /* !HISTORY_H_ */
