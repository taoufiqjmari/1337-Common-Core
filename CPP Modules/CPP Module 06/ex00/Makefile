# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 11:27:34 by tjmari            #+#    #+#              #
#    Updated: 2021/11/03 13:02:31 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = convert

INCLUDES = Scalar.hpp

SRCS = main.cpp Scalar.cpp

OBJS = main.o Scalar.o

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
