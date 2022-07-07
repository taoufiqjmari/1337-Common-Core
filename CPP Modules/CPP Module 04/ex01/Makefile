# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 13:22:40 by tjmari            #+#    #+#              #
#    Updated: 2022/07/07 00:29:23 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = animal

INCLUDES = Animal.hpp Dog.hpp Cat.hpp Brain.hpp

SRCS = main.cpp Animal.cpp Dog.cpp Cat.cpp  Brain.cpp

OBJS = main.o Animal.o Dog.o Cat.o  Brain.o

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
