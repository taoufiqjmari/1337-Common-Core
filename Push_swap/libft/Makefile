# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/29 19:54:39 by tjmari            #+#    #+#              #
#    Updated: 2021/06/17 15:36:30 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NC = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
ORANGE = \033[1;33m

NAME = libft.a

FLAGS = -Wall -Wextra -Werror -c

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c \
ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strcmp.c ft_strncmp.c \
ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \

SRCB = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJ = $(SRC:.c=.o)

OBJB = $(SRCB:.c=.o)

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) $(SRC) $(SRCB)
	@ar rc $(NAME) $(OBJ) $(OBJB)
	@ranlib $(NAME)
	@echo "$(GREEN)./$(NAME) made with bonus part included\n---------------------------------------$(NC)"

bonus:
	@gcc	$(FLAGS) $(SRCB)
	@ar rc $(NAME) $(OBJB)
	@ranlib $(NAME)
	@echo "$(GREEN)./$(NAME) (bonus) made\n----------------------$(NC)"

clean:
	@rm -f $(OBJ) $(OBJB)
	@echo "$(ORANGE)*.o deleted\n-----------$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)./$(NAME) deleted\n-----------------$(NC)"

re: fclean all

.PHONY: all clean fclean re
