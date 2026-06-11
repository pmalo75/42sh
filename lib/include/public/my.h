/*
** EPITECH PROJECT, 2026
** lib
** File description:
** lib header
*/

#ifndef MY_H_
    #define MY_H_

    #include <unistd.h>
    #include <stdlib.h>
    #include <stdbool.h>

    #define EXT_ERROR 84
    #define EXT_SUCCESS 0

//src/put
void my_putchar(char c);
void my_putstr(const char *s);
void my_putsterr(const char *s);

//src/str
int my_strcmp(const char *s1, const char *s2);
char *my_strcpy(char *dst, const char *src);
char *my_strdup(const char *s);
size_t my_strlen(const char *s);
size_t my_linelen(const char *line);
char **str_to_word_array(const char *s, char *sep);
char *my_strcat(char *dest, const char *src);
int my_strchr(const char *s, char c);
int my_strncmp(const char *s1, const char *s2, size_t n);
char *my_strndup(const char *s, size_t n);

//src/get
int my_getnbr(const char *str);

//src/memory
void free_arr(char **arr);
void *my_memset(void *s, int c, size_t n);
void *my_calloc(size_t nmemb, size_t size);
char **my_realloc_array(char **ptr, size_t old_sz, size_t new_sz);

//src/memory/array

typedef struct vec_str_s {
    char **data;
    int count;
    int cap;
} vec_str_t;

bool init_vec(vec_str_t *vec, int init_cap);
bool append_vec(vec_str_t *vec, char *el);
void free_vec(vec_str_t *vec);

int count_2d_arr(char **arr);
char **fill_2d_arr(char **arr);
char **realloc_2d_arr(char **src, char *new_element_to_add);
int *my_realloc_int(int *ptr, size_t old_cap, size_t nw_cap);

//src/parsing

    #define ASCII 256

char **my_tokenizer(
    const char *s, char *ignore, char *stop, size_t *idx);
char *parse_arr_element(char **arr, char *pattern, int start);

//src/is
int is_alpha(const char *s);
int is_number(const char *s);

#endif /* !MY_H_ */
