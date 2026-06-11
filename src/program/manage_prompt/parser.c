/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/
#include <stdlib.h>

#include "parser.h"
#include "my.h"

static int find_weakest_operator(token_bundle_t *bundle, int start, int end)
{
    int min_weight = MAX_WEIGHT + 1;
    int pivot_idx = -1;

    for (int k = start; k <= end; k++) {
        if (bundle->weights[k] > 0 && bundle->weights[k] <= min_weight) {
            min_weight = bundle->weights[k];
            pivot_idx = k;
        }
    }
    return pivot_idx;
}

static action_t check_op_type(token_bundle_t *bundle, int pivot)
{
    action_t op_type = CONTENT;

    for (size_t k = 0; OPERATOR[k].type != NULL; k++) {
        if (my_strcmp(bundle->tokens[pivot], OPERATOR[k].type) == 0)
            op_type = k;
    }
    return op_type;
}

static ast_node_t *build_leaf_node(token_bundle_t *bundle, int start, int end)
{
    ast_node_t *ast = my_calloc(1, sizeof(*ast));
    size_t i = 0;

    if (ast == NULL)
        return NULL;
    ast->type = CONTENT;
    ast->content = my_calloc((end - start) + 2, sizeof(*ast->content));
    if (ast->content == NULL) {
        free(ast);
        return NULL;
    }
    for (int k = start; k <= end; k++) {
        ast->content[i] = bundle->tokens[k];
        i++;
    }
    return ast;
}

static ast_node_t *init_op_node(token_bundle_t *bundle, int pi)
{
    ast_node_t *ast = my_calloc(1, sizeof(*ast));

    if (ast == NULL)
        return NULL;
    ast->type = check_op_type(bundle, pi);
    return ast;
}

static ast_node_t *abort_ast(ast_node_t *ast)
{
    if (ast->left != NULL)
        free_ast(ast->left);
    if (ast->right != NULL)
        free_ast(ast->right);
    free(ast);
    return NULL;
}

ast_node_t *build_ast(token_bundle_t *bundle, int start, int end)
{
    ast_node_t *ast = NULL;
    int pi = 0;

    if (start > end)
        return NULL;
    pi = find_weakest_operator(bundle, start, end);
    if (pi == -1) {
        return build_leaf_node(bundle, start, end);
    }
    ast = init_op_node(bundle, pi);
    if (ast == NULL)
        return NULL;
    ast->left = build_ast(bundle, start, pi - 1);
    if (ast->left == NULL)
        return abort_ast(ast);
    ast->right = build_ast(bundle, pi + 1, end);
    if (ast->right == NULL)
        return abort_ast(ast);
    return ast;
}

ast_node_t *parser_input(token_bundle_t *bundle)
{
    ast_node_t *ast = NULL;

    if (bundle == NULL || bundle->count == 0) {
        return NULL;
    }
    ast = build_ast(bundle, 0, bundle->count - 1);
    if (ast == NULL) {
        my_putsterr("Invalid null command.\n");
        return NULL;
    }
    return ast;
}
