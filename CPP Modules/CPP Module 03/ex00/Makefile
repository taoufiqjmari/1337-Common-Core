# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/24 18:25:34 by tjmari            #+#    #+#              #
#    Updated: 2021/10/24 18:26:05 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = claptrap

INCLUDES = ClapTrap.hpp

SRCS = main.cpp ClapTrap.cpp

OBJS = main.o ClapTrap.o

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
