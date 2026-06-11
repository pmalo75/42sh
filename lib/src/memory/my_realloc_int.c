/*
** EPITECH PROJECT, 2026
** my_realloc_int
** File description:
** my_realloc_int
*/

#include "my.h"

#include <stdlib.h>

int *edge_case(int *ptr, size_t nw_cap)
{
    int *nw_ptr = NULL;

    if (ptr == NULL) {
        nw_ptr = my_calloc(nw_cap, sizeof(*nw_ptr));
        if (nw_ptr == NULL)
            return NULL;
        return nw_ptr;
    }
    if (nw_cap == 0) {
        free(ptr);
        return NULL;
    }
    return nw_ptr;
}

int *my_realloc_int(int *ptr, size_t old_cap, size_t nw_cap)
{
    int *nw_ptr = NULL;
    size_t elements_to_cp = 0;

    if (ptr == NULL || nw_cap == 0)
        return edge_case(ptr, nw_cap);
    nw_ptr = my_calloc(nw_cap, sizeof(*nw_ptr));
    if (nw_ptr == NULL)
        return NULL;
    elements_to_cp = (old_cap < nw_cap) ? old_cap : nw_cap;
    for (int i = 0; i < elements_to_cp; i++) {
        nw_ptr[i] = ptr[i];
    }
    free(ptr);
    return nw_ptr;
}
