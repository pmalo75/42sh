/*
** EPITECH PROJECT, 2026
** G-PSU-200-PAR-2-1-42sh-10
** File description:
** autocomplete
*/

#ifndef AUTOCOMPLETE_H_
    #define AUTOCOMPLETE_H_
    #include <stdbool.h>
    #include "line_edition.h"

typedef struct autocomplete_item_s {
    char *name;
    struct autocomplete_item_s *next;
} autocomplete_item_t;


bool autocomplete(line_data_t *line);
void append_autocomplete_item(
    autocomplete_item_t **items,
    const char *new_item_name
);
void free_autocomplete_items(autocomplete_item_t *items);

#endif /* !AUTOCOMPLETE_H_ */
