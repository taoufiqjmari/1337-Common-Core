# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 09:55:15 by tjmari            #+#    #+#              #
#    Updated: 2021/10/22 09:49:10 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = zombie

SRCS = main.cpp Zombie.cpp newZombie.cpp randomChump.cpp

INCLUDES = Zombie.hpp

OBJS = main.o Zombie.o newZombie.o randomChump.o

COMPILER = clang++

VERSION = -std=c++98

FLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${SRCS} ${INCLUDES}
	${COMPILER} ${VERSION} ${FLAGS} ${SRCS} -o ${NAME}

clean:
	@rm -f ${OBJ}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
