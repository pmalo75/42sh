/*
** EPITECH PROJECT, 2026
** my_realloc_array
** File description:
** my_realloc_array
*/

#include "my.h"

#include <stdlib.h>

static char **edge_case(char **ptr, size_t nw_cap)
{
    char **nw_ptr = NULL;

    if (ptr == NULL) {
        nw_ptr = my_calloc(nw_cap, sizeof(*nw_ptr));
        if (nw_ptr == NULL)
            return NULL;
    }
    if (nw_cap == 0)
        free(ptr);
    return nw_ptr;
}

char **my_realloc_array(char **ptr, size_t old_sz, size_t new_sz)
{
    char **new_ptr = NULL;
    size_t elements_to_cp = 0;

    if (ptr == NULL || new_sz == 0)
        return edge_case(ptr, new_sz);
    new_ptr = my_calloc(new_sz, sizeof(char *));
    if (new_ptr == NULL)
        return NULL;
    elements_to_cp = (old_sz < new_sz) ? old_sz : new_sz;
    for (size_t i = 0; i < elements_to_cp; i++) {
        new_ptr[i] = ptr[i];
    }
    free(ptr);
    return new_ptr;
}
