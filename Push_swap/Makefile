# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/06 15:06:53 by tjmari            #+#    #+#              #
#    Updated: 2021/06/22 19:31:09 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NC = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
ORANGE = \033[1;33m

NAME = push_swap
NAME_BONUS = checker
LIBFT = libft.a

FLAGS = -Wall -Wextra -Werror

# PUSH_SWAP
INCLUDES = ./PS_SRCS/includes/push_swap.h
SRCS = ./PS_SRCS/srcs/main.c \
		./PS_SRCS/srcs/utils.c \
		./PS_SRCS/srcs/list.c \
		./PS_SRCS/srcs/list_utils.c \
		./PS_SRCS/srcs/swaps.c \
		./PS_SRCS/srcs/pushes.c \
		./PS_SRCS/srcs/rotates.c \
		./PS_SRCS/srcs/reverse_rotates.c \
		./PS_SRCS/srcs/to_sort.c \
		./PS_SRCS/srcs/sort_else_utils.c \

OBJS = $(SRCS:.c=.o)

# CHECKER
INCLUDES_BONUS = ./CH_SRCS/includes/checker.h
SRCS_BONUS = ./CH_SRCS/srcs/main.c \
		./CH_SRCS/srcs/list.c \
		./CH_SRCS/srcs/list_utils.c \
		./CH_SRCS/srcs/swaps.c \
		./CH_SRCS/srcs/pushes.c \
		./CH_SRCS/srcs/rotates.c \
		./CH_SRCS/srcs/reverse_rotates.c \
		./CH_SRCS/srcs/operations.c

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

# PUSH_SWAP
all: $(NAME)

$(NAME): $(INCLUDES) $(SRCS)
	@make -C ./libft
	@mv ./libft/$(LIBFT) ./
	@echo "$(GREEN)PUSH_SWAP: ./$(LIBFT) moved to ./\n--------------------------------$(NC)"
	@gcc $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)PUSH_SWAP: ./$(NAME) made\n---------------------------$(NC)"

debug: $(NAME).dSYM

$(NAME).dSYM: $(INCLUDES) $(SRCS)
	@make -C ./libft
	@mv ./libft/$(LIBFT) ./
	@echo "$(GREEN)./$(LIBFT) moved to ./\n---------------------$(NC)"
	@gcc $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME) -g -fsanitize=address
	@echo "$(GREEN)PUSH_SWAP: ./$(NAME) made by -g -fsanitize=address flags\n----------------------------------------------------------$(NC)"

# CHECKER
bonus: $(NAME_BONUS)

$(NAME_BONUS): $(INCLUDES_BONUS) $(SRCS_BONUS)
	@make -C ./libft
	@mv ./libft/$(LIBFT) ./
	@echo "$(GREEN)CHECKER: ./$(LIBFT) moved to ./\n------------------------------$(NC)"
	@gcc $(FLAGS) $(SRCS_BONUS) $(LIBFT) -o $(NAME_BONUS)
	@echo "$(GREEN)CHECKER: ./$(NAME_BONUS) made\n-----------------------$(NC)"

bonus_debug: $(NAME_BONUS).dSYM

$(NAME_BONUS).dSYM: $(INCLUDES_BONUS) $(SRCS_BONUS)
	@make -C ./libft
	@mv ./libft/$(LIBFT) ./
	@echo "$(GREEN)./$(LIBFT) moved to ./\n---------------------$(NC)"
	@gcc $(FLAGS) $(SRCS_BONUS) $(LIBFT) -o $(NAME_BONUS) -g -fsanitize=address
	@echo "$(GREEN)CHECKER: ./$(NAME_BONUS) made by -g -fsanitize=address flags\n------------------------------------------------------$(NC)"

# CLEANING
clean:
	@make clean -C ./LIBFT

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(RED)PUSH_SWAP: ./$(LIBFT) deleted\n----------------------------$(NC)"
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "$(RED)PUSH_SWAP: ./$(NAME) AND ./$(NAME_BONUS) deleted\n--------------------------------------------$(NC)"
	@rm -rf .vscode $(NAME).dSYM $(NAME_BONUS).dSYM
	@echo "$(RED)PUSH_SWAP: debugging files deleted\n----------------------------------$(NC)"

re: fclean all
re_bonus: fclean bonus

.PHONY: all clean fclean re

# RULES
rules:
	@echo "Rules (1..4) doesn't relink"
	@echo "$(GREEN)1. make$(NC)"
	@echo "$(GREEN)2. make debug$(NC)"
	@echo "$(GREEN)3. make bonus$(NC)"
	@echo "$(GREEN)4. make bonus_debug$(NC)"
	@echo "$(ORANGE)5. make clean$(NC)"
	@echo "$(RED)6. make fclean$(NC)"
	@echo "$(GREEN)7. make re$(NC)"
	@echo "$(GREEN)8. make re_bonus$(NC)"
