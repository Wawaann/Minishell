SRC	=	main.c			\

SRC		:=	$(addprefix src/, $(SRC))

OBJ_DIR	=	obj/
OBJ		=	$(patsubst src/%.c,$(OBJ_DIR)%.o,$(SRC))

INCLUDE	=	-I./include/

LIB		=	-L./lib -lft -lreadline

FLAG	=	-Wall -Wextra -Werror -g3

NAME	=	minishell

DEFAULT	=	\033[0m
GREEN	=	\033[0;32m
RED		=	\033[0;31m
YELLOW	=	\033[0;33m
CYAN	=	\033[0;36m
BOLD	=	\033[1m

$(OBJ_DIR)%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
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
