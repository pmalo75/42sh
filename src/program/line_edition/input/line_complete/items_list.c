/*
** EPITECH PROJECT, 2026
** G-PSU-200-PAR-2-1-42sh-10
** File description:
** items_list
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "line_edition.h"
#include "autocomplete.h"

static autocomplete_item_t *create_autocomplete_item(const char *name)
{
    autocomplete_item_t *item = calloc(1, sizeof(autocomplete_item_t));

    if (!item)
        return NULL;
    item->name = strdup(name);
    if (!item->name) {
        free(item);
        return NULL;
    }
    return item;
}

static bool check_valid_autocomplete_item(
    const char *name,
    const autocomplete_item_t *items
)
{
    if (strcmp(name, ".") == 0 ||
        strcmp(name, "..") == 0)
        return false;
    while (items != NULL) {
        if (strcmp(items->name, name) == 0)
            return false;
        items = items->next;
    }
    return true;
}

void append_autocomplete_item(
    autocomplete_item_t **items,
    const char *new_item_name
)
{
    autocomplete_item_t *items_cpy = *items;
    autocomplete_item_t *temp_item = NULL;

    if (!check_valid_autocomplete_item(new_item_name, *items))
        return;
    temp_item = create_autocomplete_item(new_item_name);
    if (!temp_item)
        return;
    if (*items == NULL) {
        *items = temp_item;
        return;
    }
    while (items_cpy->next != NULL)
        items_cpy = items_cpy->next;
    items_cpy->next = temp_item;
}

void free_autocomplete_items(autocomplete_item_t *items)
{
    autocomplete_item_t *next_item = NULL;

    if (items == NULL)
        return;
    while (items != NULL) {
        free(items->name);
        next_item = items->next;
        free(items);
        items = next_item;
    }
}
