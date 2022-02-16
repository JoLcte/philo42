# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 19:33:43 by jlecomte          #+#    #+#              #
#    Updated: 2022/02/14 13:58:03 by jlecomte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INC = includes

CC = gcc
CFLAGS = -Werror -Wall -Wextra -I$(INC)

LIBS =

SRC_DIR = src
OBJ_DIR = obj

SRC := $(SRC_DIR)/main.c\
	$(SRC_DIR)/parsing/ast.c\
	$(SRC_DIR)/parsing/build_ast.c

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# ----- COLORS -----
ON_BLUE = \033[44m
ON_CYAN = \033[46m
ON_PURPLE = \033[45m
BBLUE = \033[1;34m
BCYAN = \033[1;36m
BGREEN = \033[1;32m
BLUE = \033[0;34m
CYAN = \033[0;36m
PURPLE = \033[0;35m
EOC = \033[m
# ------------------

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $(OBJ_DIR)/$*)
	@$(CC) $(CFLAGS) -c -o $@ $^ $(LIBS)
	@echo "$(CYAN)Creating: $(@:%=%)$(EOC)"

$(NAME) : $(OBJ)
	@echo "\033[44m *** Compiling Libft Library ***\033[m"
	@make -C libft
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo "$(ON_BLUE)- $(NAME) Compilation Completed -$(EOC)"
clean:
	@if [ -d $(OBJ_DIR) ]; then rm -rf $(OBJ_DIR) && echo "$(PURPLE)Removing: $(NAME) Object Files$(EOC)"; else echo "make: No $(NAME) objects to remove."; fi

fclean: clean
	@make fclean -C libft
	@if [ -f $(NAME) ]; then rm -f $(NAME) && echo "$(ON_PURPLE)Removing - $(NAME) -$(EOC)"; else echo "make: No binary $(NAME) to remove."; fi;

re: fclean all

.PHONY: all clean fclean re bonus
