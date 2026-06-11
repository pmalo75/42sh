##
## EPITECH PROJECT, 2026
## mysh
## File description:
## mysh Makefile
##

# ========================
# Variables declaration
# ========================

NAME = 42sh

CC := epiclang

# Librarie declaration
LIBDIR = lib
LIBNAME = libmy.a
LIB = $(LIBDIR)/$(LIBNAME)

# Lib header declaration
INCLIB = $(LIBDIR)/include/public

# Files declaration
D_SRC = src
MAIN = $(D_SRC)/main.c

D_PROGRAM = $(D_SRC)/program

D_BUILTINS = $(D_PROGRAM)/builtins
F_BUILTINS = my_env.c				\
			my_exit.c				\
			my_unset.c				\
			my_history.c			\
			alias/alias.c			\
			alias/display_aliases.c	\
			credits/credits.c		\
			mediaplayer/command.c	\
			mediaplayer/setup.c		\
			mediaplayer/utils.c		\
			mediaplayer/decode.c	\
			mediaplayer/render.c	\
			mediaplayer/input.c		\
			mediaplayer/geometry.c

D_LOCAL = $(D_BUILTINS)/local
F_LOCAL = init_local_var.c \
		  set_builtin.c \
		  unset_builtin.c

D_JOB_BUILTIN = $(D_BUILTINS)/jobs
F_JOB_BUILTIN = jobs.c				\
				bg.c				\
				fg.c				\
				restart_job.c

D_CD = $(D_BUILTINS)/cd
F_CD = move_directory.c \
		move_home.c \
		move_old_dir.c \
		my_cd.c

D_SETENV = $(D_BUILTINS)/setenv
F_SETENV = add_new_env_var.c \
		my_setenv.c \
		replace_env_var.c \
		set_environment_var.c

D_PARSING = $(D_PROGRAM)/parsing
F_PARSING =	get_cmd_path.c \
			get_path_var.c \
			is_file_ok.c

D_LINE_EDITION = $(D_PROGRAM)/line_edition

D_TERMIOS = $(D_LINE_EDITION)/termios
F_TERMIOS =	termios.c

D_INPUT = $(D_LINE_EDITION)/input
F_INPUT = read_line.c					\
		  read_utils.c					\
		  line_complete/line_complete.c	\
		  line_complete/items_list.c

D_KHISTORY = $(D_LINE_EDITION)/history
F_KHISTORY = keybinds_history.c	\
		  load_history.c

D_RUN = $(D_PROGRAM)/run
F_RUN = execute.c			\
 		execute_cmd.c		\
 		run_shell.c			\
 		prompt.c			\
		rules.c				\
		redirections.c		\
		exec_builtins.c

D_JOBS = $(D_RUN)/jobs
F_JOBS = store_jobs.c	\
		 jobs_cleanup.c

D_HISTORY = $(D_PROGRAM)/history
F_HISTORY = make_history.c	\
			utils_history.c

D_HISTORY = $(D_PROGRAM)/history
F_HISTORY = make_history.c	\
			utils_history.c

D_MANAGE_PROMPT = $(D_PROGRAM)/manage_prompt
F_MANAGE_PROMPT = lexer.c								\
				parser.c								\
				free_content.c							\
				replace_aliases/replace_aliases.c		\
				replace_aliases/replace_single_value.c

SRC = $(MAIN) \
 		$(addprefix $(D_LOCAL)/, $(F_LOCAL)) \
		$(addprefix $(D_MANAGE_PROMPT)/, $(F_MANAGE_PROMPT))	\
	 	$(addprefix $(D_RUN)/, $(F_RUN))						\
		$(addprefix $(D_TERMIOS)/, $(F_TERMIOS)) \
		$(addprefix $(D_INPUT)/, $(F_INPUT)) \
		$(addprefix $(D_KHISTORY)/, $(F_KHISTORY)) \
		$(addprefix $(D_HISTORY)/, $(F_HISTORY)) \
 		$(addprefix $(D_BUILTINS)/, $(F_BUILTINS))				\
 		$(addprefix $(D_CD)/, $(F_CD))							\
 		$(addprefix $(D_SETENV)/, $(F_SETENV))					\
 		$(addprefix $(D_PARSING)/, $(F_PARSING))				\
 		$(addprefix $(D_JOBS)/, $(F_JOBS))						\
 		$(addprefix $(D_JOB_BUILTIN)/, $(F_JOB_BUILTIN))

# exctraction of the main for criterion tests
SRC_NOMAIN = $(filter-out $(MAIN), $(SRC))
TEST_NAME = unit_tests

# Flags
CPPFLAGS = -iquote include -iquote $(INCLIB)
CFLAGS = -Wall -Wextra -MMD -MP -MF $(@:.o=.d) -MT $@
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)
LIBS    := libavformat libavcodec libswscale libavutil
LDFLAGS = -L$(LIBDIR) $(shell pkg-config --cflags $(LIBS))
LDLIBS = -lmy $(shell pkg-config --libs $(LIBS))

# ================
# Default calls
# ================

all: $(NAME)

install_deps:
	sudo apt update
	sudo apt install -y \
		pkg-config \
		libavformat-dev \
		libavcodec-dev \
		libswscale-dev \
		libavutil-dev

$(LIB):
	$(MAKE) -C $(LIBDIR)

$(NAME): $(OBJ) $(SUBJECT_LIB) $(LIB)
	$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

unit_test: fclean $(NAME)
	$(CC) -o $(TEST_NAME) tests/*.c $(SRC_NOMAIN) \
	$(CPPFLAGS) $(LDFLAGS) $(LDLIBS) --coverage -lcriterion

tests_run: unit_test
	./$(TEST_NAME)

tests_coverage: tests_run
	gcovr --gcov-executable "llvm-cov gcov" --exclude tests/

debug: re
debug: CPPFLAGS += -g3

clean:
	find . \( -name "*.o" -o -name "*.d" \) -delete

clean_tests:
	$(RM) $(TEST_NAME)
	find . \( -name "*.gcda" -o -name "*.gcno" \) -delete

fclean: clean clean_tests
	$(RM) $(NAME)
	find . -name *.a -delete

re: fclean all

.PHONY: all clean fclean re unit_test tests_run coverage install_deps

-include $(DEP)
