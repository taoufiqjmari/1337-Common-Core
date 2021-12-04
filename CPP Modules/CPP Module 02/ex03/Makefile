# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 16:26:59 by tjmari            #+#    #+#              #
#    Updated: 2021/10/24 17:44:07 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fixed

INCLUDES = Fixed.hpp Point.hpp

SRCS = main.cpp Fixed.cpp Point.cpp bsp.cpp

OBJS = main.o

COMPILER = clang++

VERSION = -std=c++98

FLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${INCLUDES} ${SRCS}
	${COMPILER} ${VERSION} ${FLAGS} ${SRCS} -o ${NAME}

clean:
	@rm -f ${OBJ}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
