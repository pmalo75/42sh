/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/

#include <stdlib.h>

#include "parser.h"

void free_token_bundle(token_bundle_t *value)
{
    if (value == NULL)
        return;
    for (size_t i = 0; value->tokens[i] != NULL; i++)
        free(value->tokens[i]);
    free(value->tokens);
    free(value->weights);
    free(value);
}

void free_ast(ast_node_t *node)
{
    if (node == NULL)
        return;
    free_ast(node->left);
    free_ast(node->right);
    if (node->content != NULL)
        free(node->content);
    free(node);
}
