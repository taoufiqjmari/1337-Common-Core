# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/26 19:12:34 by tjmari            #+#    #+#              #
#    Updated: 2021/10/14 10:14:31 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NC = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
ORANGE = \033[1;33m

COMPILER = gcc
FLAGS = -Wall -Wextra -Werror #-fsanitize=thread
DEBUG = -g
LIBS = -pthread

NAME = philo

INCLUDES = ./includes/philo.h

SRCS = ./srcs/main.c \
		./srcs/ft_atoi.c \
		./srcs/routine.c \
		./srcs/supervisor.c \
		./srcs/utils.c

all: $(NAME)

$(NAME): $(INCLUDES) $(SRCS)
	@$(COMPILER) $(FLAGS) $(LIBS) $(SRCS) -o $(NAME)
	@echo "$(GREEN)PHILO: ./$(NAME) made\n-------------------$(NC)"

clean:
	@rm -rf ../.vscode $(NAME).dSYM
	@echo "$(RED)PHILO: debugging files deleted\n------------------------------$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)PHILO: ./$(NAME) deleted\n----------------------$(NC)"

re: fclean all

.PHONY: all clean fclean re
