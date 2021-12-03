# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/09 15:05:38 by tjmari            #+#    #+#              #
#    Updated: 2020/03/12 14:04:34 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror -c

SRC = ft_printf.c ft_parameters.c ft_width.c ft_precision.c \
ft_character.c ft_string.c ft_pointer.c ft_integer.c \
ft_unsigned_int.c ft_hexadecimal.c ft_percent.c \
libft_adfix.c libft_str.c libft_put.c itox.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
