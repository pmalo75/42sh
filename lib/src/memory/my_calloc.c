/*
** EPITECH PROJECT, 2026
** my_calloc
** File description:
** my_calloc
*/

#include "my.h"

void *my_calloc(size_t nmemb, size_t size)
{
    void *ptr = malloc(nmemb * size);

    if (!ptr)
        return NULL;
    my_memset(ptr, 0, nmemb * size);
    return ptr;
}
