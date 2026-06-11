/*
** EPITECH PROJECT, 2026
** G-PSU-200-PAR-2-1-42sh-10
** File description:
** replace_single_value
*/

#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "my.h"

static size_t get_array_size(char **array)
{
    size_t count = 0;

    while (*array) {
        count++;
        array++;
    }
    return count;
}

static void update_new_values(token_bundle_t *tokens_bundle,
    char **new_tokens,
    size_t tokens_index,
    size_t old_array_size)
{
    char **new_array = tokens_bundle->tokens;
    int *weights_array = tokens_bundle->weights;
    size_t values_to_replace_size = get_array_size(new_tokens);

    free(new_array[tokens_index]);
    (void)memmove(
        &new_array[tokens_index + values_to_replace_size],
        &new_array[tokens_index + 1],
        (old_array_size - tokens_index) * sizeof(char *)
    );
    (void)memmove(
        &weights_array[tokens_index + values_to_replace_size],
        &weights_array[tokens_index + 1],
        (old_array_size - tokens_index) * sizeof(int)
    );
    for (size_t i = 0; i < values_to_replace_size; i++) {
        new_array[tokens_index + i] = strdup(new_tokens[i]);
        weights_array[tokens_index + i] = 0;
    }
}

static void reallocate_tokens_array(token_bundle_t *tokens_bundle,
    size_t tokens_index,
    char *new_value,
    int *tokens_count)
{
    char ***tokens = &tokens_bundle->tokens;
    char **new_tokens = str_to_word_array(new_value, " \t");
    size_t new_array_size = 0;
    size_t old_array_size = get_array_size(*tokens);

    if (new_tokens == NULL)
        return;
    new_array_size = old_array_size + get_array_size(new_tokens) + 1;
    *tokens = realloc(*tokens, (new_array_size + 1) * sizeof(char *));
    tokens_bundle->weights = realloc(tokens_bundle->weights,
        (new_array_size + 1) * sizeof(int));
    if (*tokens == NULL || tokens_bundle->weights == NULL) {
        free_arr(new_tokens);
        return;
    }
    update_new_values(tokens_bundle, new_tokens, tokens_index, old_array_size);
    *tokens_count += (get_array_size(new_tokens) - 1);
    free_arr(new_tokens);
}

void replace_value(token_bundle_t *tokens_bundle,
    size_t tokens_index,
    char *alias_line,
    int *tokens_count
)
{
    char *alias_line_dup = strdup(alias_line);
    char *save_ptr = NULL;
    char *alias_line_token = NULL;

    if (alias_line_dup == NULL)
        return;
    alias_line_token = strtok_r(alias_line_dup, "=", &save_ptr);
    alias_line_token = strtok_r(NULL, "=", &save_ptr);
    alias_line_token++;
    alias_line_token[strcspn(alias_line_token, "\"")] = '\0';
    reallocate_tokens_array(tokens_bundle,
        tokens_index,
        alias_line_token,
        tokens_count
    );
    free(alias_line_dup);
}
