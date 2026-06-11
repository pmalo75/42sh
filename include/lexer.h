/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#ifndef LEXER_H_
    #define LEXER_H_

    #include <stdlib.h>
    #include "global.h"

    #define MAX_WEIGHT 4

typedef enum {
    RED_RIGHT_APP,
    HEREDOC,
    LOGIC_OR,
    PIPE,
    RED_RIGHT,
    RED_LEFT,
    SEMICOLON,
    LOGIC_AND,
    CONTENT
} action_t;

typedef struct operator_s {
    char *type;
    int len;
    int weight;
} operator_t;

static const operator_t OPERATOR[] = {
    [RED_RIGHT_APP] = {">>", 2, 4},
    [HEREDOC] = {"<<", 2, 4},
    [LOGIC_OR] = {"||", 2, 2},
    [PIPE] = {"|", 1, 3},
    [RED_RIGHT] = {">", 1, 4},
    [RED_LEFT] = {"<", 1, 4},
    [SEMICOLON] = {";", 1, 1},
    [LOGIC_AND] = {"&&", 2, 2},
    [CONTENT] = {NULL, 0, 0}
};

typedef struct token_bundle_s {
    char **tokens;
    int *weights;
    int cap;
    int count;
} token_bundle_t;

token_bundle_t *lexer_input(const char *prompt, env_t *env);
void replace_aliases(token_bundle_t *tokens,
    env_t *env,
    size_t recursion_count);
void replace_value(token_bundle_t *tokens_bundle,
    size_t tokens_index,
    char *alias_line,
    int *tokens_count
);

//free bundle
void free_token_bundle(token_bundle_t *value);

#endif /* !LEXER_H_ */
