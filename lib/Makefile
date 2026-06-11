##
## EPITECH PROJECT, 2025
## lib
## File description:
## lib makefile
##

# ========================
# Variables declaration
# ========================

NAME = libmy.a

CC := clang

# Headers declaration
F_INCLUDE = include

F_PUB_INCLUDE = $(F_INCLUDE)/public
F_PRIV_INCLUDE = $(F_INCLUDE)/private

# Files declaration
F_SRC = src

F_MEMORY = $(F_SRC)/memory
MEMORY = free_arr.c \
		my_memset.c \
		my_calloc.c \
		my_realloc_array.c \
		my_realloc_int.c \
		vector.c

F_ARRAY = $(F_MEMORY)/array
ARRAY = count.c \
		fill.c \
		realloc_2d_arr.c

F_PUT = $(F_SRC)/put
PUT = my_putchar.c \
		my_putstr.c \
		my_putnbr.c \
		my_putsterr.c

F_STR = $(F_SRC)/str
STR = my_strcmp.c \
		my_strcpy.c \
		my_strdup.c \
		my_strlen.c \
		my_linelen.c \
		str_to_word_array.c \
		my_strcat.c \
		my_strchr.c \
		my_strncmp.c \
		my_strndup.c

F_GET = $(F_SRC)/get
GET = my_getnbr.c

F_PARSING = $(F_SRC)/parsing
PARSING = parse_2d_arr.c \
		my_tokenizer.c

F_IS = $(F_SRC)/is
IS = is_alpha.c \
	is_number.c

SRC =	$(addprefix $(F_PUT)/, $(PUT)) \
		$(addprefix $(F_STR)/, $(STR)) \
		$(addprefix $(F_GET)/, $(GET)) \
		$(addprefix $(F_MEMORY)/, $(MEMORY)) \
		$(addprefix $(F_ARRAY)/, $(ARRAY)) \
		$(addprefix $(F_PARSING)/, $(PARSING)) \
		$(addprefix $(F_IS)/, $(IS))

# Flags
CPPFLAGS = -iquote $(F_PRIV_INCLUDE) -iquote $(F_PUB_INCLUDE)
CFLAGS = -Wall -MMD -MP -MF $(@:.o=.d) -MT $@
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)

# ================
# Default calls
# ================

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

# =================
# cleaning rules
# =================

clean:
	find . \( -name "*.o" -o -name "*.d" \) -delete

fclean:	clean
	$(RM) $(NAME)

# ==========
# Restart
# ==========

re: fclean all

# PHONY
.PHONY: all clean fclean re

-include $(DEP)
