/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** A 42sh component
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "my_sh_def.h"
#include "my.h"
#include "lexer.h"
#include "global.h"

static token_bundle_t *init_bundle(void)
{
    token_bundle_t *result = my_calloc(1, sizeof(*result));

    if (result == NULL)
        return NULL;
    result->cap = 10;
    result->count = 0;
    result->tokens = my_calloc(10, sizeof(*result->tokens));
    if (result->tokens == NULL) {
        free(result);
        return NULL;
    }
    result->weights = my_calloc(10, sizeof(*result->weights));
    if (result->weights == NULL) {
        free(result->tokens);
        free(result);
        return NULL;
    }
    return result;
}

static int add_token(token_bundle_t *bundle, char *str, int weight)
{
    if (bundle->count >= bundle->cap) {
        bundle->cap *= 2;
        bundle->tokens = my_realloc_array(
            bundle->tokens, bundle->count, bundle->cap);
        bundle->weights = my_realloc_int(
            bundle->weights, bundle->count, bundle->cap);
        if (bundle->tokens == NULL || bundle->weights == NULL)
            return -1;
    }
    bundle->tokens[bundle->count] = str;
    bundle->weights[bundle->count] = weight;
    bundle->count++;
    return 0;
}

static int extract_operator(
    token_bundle_t *bundle, const char *prompt, int *i)
{
    char *op_str = NULL;

    for (size_t j = 0; OPERATOR[j].type != NULL; j++) {
        if (my_strncmp(&prompt[*i], OPERATOR[j].type, OPERATOR[j].len) != 0) {
            continue;
        }
        op_str = my_strndup(&prompt[*i], OPERATOR[j].len);
        if (op_str == NULL)
            return -1;
        if (add_token(bundle, op_str, OPERATOR[j].weight) == -1) {
            free(op_str);
            return -1;
        }
        *i = *i + OPERATOR[j].len;
        return FIND;
    }
    return NOT_FOUND;
}

static bool is_op_ahead(const char *str)
{
    for (size_t j = 0; OPERATOR[j].type != NULL; j++) {
        if (my_strncmp(str, OPERATOR[j].type, OPERATOR[j].len) == 0)
            return true;
    }
    return false;
}

static void get_word_len(const char *prompt,
    bool is_under_double_quotes,
    int *i, size_t *len)
{
    for (; prompt[*i + *len] != '\0'; (*len)++) {
        if (is_under_double_quotes && prompt[*i + *len] == '\"')
            break;
        if (!is_under_double_quotes &&
            (prompt[*i + *len] == ' ' || prompt[*i + *len] == '\t'))
            break;
        if (!is_under_double_quotes && is_op_ahead(&prompt[*i + *len]) == true)
            break;
    }
}

static char *allocate_word(bool is_under_double_quotes,
    const char *prompt,
    int *i,
    size_t len)
{
    char *word = NULL;

    if (!is_under_double_quotes)
        word = my_strndup(&prompt[*i], len);
    else {
        word = my_strndup(&prompt[*i + 1], len);
        word[my_strlen(word) - 1] = '\0';
    }
    return word;
}

static size_t get_occurences(const char *str, const char c)
{
    size_t count = 0;

    while (*str) {
        if (*str == c)
            count++;
        str++;
    }
    return count;
}

static int extract_word(
    token_bundle_t *bundle, const char *prompt, int *i)
{
    size_t len = 0;
    char *word = NULL;
    bool is_under_double_quotes = (prompt[*i] == '\"');

    if (is_under_double_quotes && get_occurences(prompt, '\"') != 2)
        return ERROR;
    if (is_under_double_quotes)
        len++;
    get_word_len(prompt, is_under_double_quotes, i, &len);
    word = allocate_word(is_under_double_quotes, prompt, i, len);
    if (word == NULL)
        return ERROR;
    if (add_token(bundle, word, OPERATOR[CONTENT].weight) == -1) {
        free(word);
        return ERROR;
    }
    *i = *i + len;
    if (is_under_double_quotes)
        (*i)++;
    return SUCCESS;
}

static int tokenize_prompt(token_bundle_t *result, const char *prompt)
{
    int i = 0;
    int status = 0;

    while (prompt[i] != '\0') {
        if (prompt[i] == ' ' || prompt[i] == '\t') {
            i++;
            continue;
        }
        status = extract_operator(result, prompt, &i);
        if (status == -1)
            return -1;
        if (status == 1)
            continue;
        if (extract_word(result, prompt, &i) == ERROR)
            return -1;
    }
    return 0;
}

token_bundle_t *lexer_input(const char *prompt, env_t *env)
{
    token_bundle_t *result = NULL;

    if (prompt == NULL)
        return NULL;
    result = init_bundle();
    if (result == NULL)
        return NULL;
    if (tokenize_prompt(result, prompt) == -1) {
        free_token_bundle(result);
        return NULL;
    }
    replace_aliases(result, env, 1);
    return result;
}
