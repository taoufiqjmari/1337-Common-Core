# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/20 12:00:58 by tjmari            #+#    #+#              #
#    Updated: 2021/02/24 12:08:06 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NC = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
ORANGE = \033[1;33m

NAME = libasm.a
FLAGS = -f macho64

SRCS = ./srcs/ft_strlen.s ./srcs/ft_strcpy.s ./srcs/ft_strcmp.s \
		./srcs/ft_write.s ./srcs/ft_read.s ./srcs/ft_strdup.s
OBJS = $(SRCS:.s=.o)

%.o: %.s
	@nasm $(FLAGS) -o $@ $<

all: $(NAME)

$(NAME): $(SRCS) $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@echo "$(GREEN)./$(NAME) made\n---------------$(NC)"

clean:
	@rm -f $(OBJS)
	@echo "$(ORANGE)*.o deleted\n-----------$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)./$(NAME) deleted\n------------------$(NC)"

re: fclean all
