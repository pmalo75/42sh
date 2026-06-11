/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#ifndef PARSER_H_
    #define PARSER_H_

    #include "lexer.h"

typedef struct ast_node_s {
    action_t type;
    char **content;
    struct ast_node_s *left;
    struct ast_node_s *right;
} ast_node_t;

//create tree
ast_node_t *parser_input(token_bundle_t *bundle);

//free tree
void free_ast(ast_node_t *node);

#endif /* !PARSER_H_ */
