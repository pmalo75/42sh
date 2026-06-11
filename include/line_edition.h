/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#ifndef LINE_EDITION_H_
    #define LINE_EDITION_H_

    #define INIT_BUF_SZ 64
    #define USER_PRE_LEN 5
    #define PR_EXTRA_LEN 70
    #define CMD_INDEX 1

    #define ESCAPE_CHAR 27
    #define BACKSPACE_CHAR 127
    #define CTRL_CHAR_MAX 32

    #define ARROW_LEFT 'D'
    #define ARROW_RIGHT 'C'
    #define ARROW_UP 'A'
    #define ARROW_DOWN 'B'

    #define NEWLINE_CHAR '\n'
    #define TAB_CHAR '\t'
    #define EOF_CHAR 4
    #define CTRL_C_CHAR 3

    #define CURSOR_LEFT_SQ "\033[D"
    #define CURSOR_RIGHT_SQ "\033[C"
    #define CLEAR_LINE_SQ "\033[K"

    #include <stdbool.h>
    #include <stddef.h>
    #include <termios.h>

    #include "global.h"

typedef struct terminal_s {
    struct termios old_term;
} terminal_t;

typedef struct line_data_s {
    char *buffer;
    char *prompt;
    char **history;
    size_t len;
    size_t capacity;
    size_t cursor;
    int history_index;
    bool is_eof;
} line_data_t;

typedef bool (*key_handler_t)(line_data_t *line);

typedef struct keybind_s {
    char key;
    key_handler_t handler;
} keybind_t;

char *get_prompt(env_t *env);
bool handle_backspace(line_data_t *line);
bool handle_esc_sq(line_data_t *line);
bool handle_ctrl_d(line_data_t *line);
bool handle_ctrl_c(line_data_t *line);
bool handle_input(env_t *env, line_data_t *line, char c);
char *read_line(env_t *env);
void redraw_line(const line_data_t *line);
void enable_raw_mode(terminal_t *term);
void disable_raw_mode(terminal_t *term);
bool handle_history_up(line_data_t *line);
bool handle_history_down(line_data_t *line);
char **load_history(void);
int get_history_size(char **history);

static const keybind_t KEYBINDS[] = {
    {ESCAPE_CHAR, handle_esc_sq},
    {BACKSPACE_CHAR, handle_backspace},
    {EOF_CHAR, handle_ctrl_d},
    {CTRL_C_CHAR, handle_ctrl_c},
    {0, NULL}
};

#endif /* !LINE_EDITION_H_ */
