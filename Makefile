SRC	=	main.c							\
		free.c							\
		get_prompt.c					\
		signal.c						\
		exec/exec.c						\
		exec/exec_utils.c				\
		exec/error.c					\
		exec/handle_heredoc.c			\
		exec/handle_pipes.c				\
		exec/handle_redir.c				\
		parsing/error.c					\
		parsing/get_command.c			\
		parsing/get_redirs.c			\
		parsing/refactor.c				\
		parsing/tokenize.c				\
		parsing/token_utils.c			\
		parsing/utils.c					\
		builts_in/pwd.c					\
		builts_in/cd.c					\
		builts_in/env.c					\
		builts_in/export.c				\
		builts_in/export_utils.c		\
		builts_in/unset.c				\
		builts_in/echo.c				\
		builts_in/exit.c				\
		builts_in/handle_builts_in.c	\

SRC		:=	$(addprefix src/, $(SRC))

OBJ_DIR	=	obj/
OBJ		=	$(patsubst src/%.c,$(OBJ_DIR)%.o,$(SRC))

ifeq ($(shell uname), Darwin)
	INCLUDE	=	-I./include/ -I/opt/homebrew/opt/readline/include/
	LIB		=	-L./lib -lft -L/opt/homebrew/opt/readline/lib/ -lreadline
else
	INCLUDE	=	-I./include/
	LIB		=	-L./lib -lft -lreadline
endif

FLAG	=	-Wall -Wextra -Werror -g

NAME	=	minishell

DEFAULT	=	\033[0m
GREEN	=	\033[0;32m
RED		=	\033[0;31m
YELLOW	=	\033[0;33m
CYAN	=	\033[0;36m
BOLD	=	\033[1m

$(OBJ_DIR)%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/exec
	@mkdir -p $(OBJ_DIR)/builts_in
	@echo "$(CYAN)Compiling:$(DEFAULT) $<"
	@gcc $(FLAG) $(INCLUDE) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJ)
	@if [ ! -e ./lib/libft.a ]; then 						\
		echo "$(YELLOW)$(BOLD)Creating:$(DEFAULT) libft";	\
		make -C lib/ --quiet;								\
		echo "$(GREEN)$(BOLD)Done$(DEFAULT)";				\
	fi
	@echo "$(YELLOW)$(BOLD)Creating:$(DEFAULT) ./$(NAME)"
	@gcc -o $(NAME) $(OBJ) $(LIB) $(INCLUDE) $(FLAG)
	@echo "$(GREEN)$(BOLD)Done$(DEFAULT)"

clean:
	@echo "$(RED)Cleaning:$(DEFAULT) $(OBJ)"
	@make clean -C lib/ --quiet
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Done$(DEFAULT)"

fclean:	clean
	@echo "$(RED)Cleaning: $(DEFAULT)$(NAME)"
	@make fclean -C lib --quiet
	@rm -f $(NAME)
	@rm -f code
	@echo "$(GREEN)Done$(DEFAULT)"

re:	fclean all

.PHONY: all clean fclean re
