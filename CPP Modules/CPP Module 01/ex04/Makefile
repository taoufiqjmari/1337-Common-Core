# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 13:40:48 by tjmari            #+#    #+#              #
#    Updated: 2021/10/21 14:24:11 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = replace

SRCS = main.cpp

OBJS = main.o

COMPILER = clang++

VERSION = -std=c++98

FLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${SRCS}
	${COMPILER} ${VERSION} ${FLAGS} ${SRCS} -o ${NAME}

clean:
	@rm -f ${OBJ}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
