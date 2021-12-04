# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 11:23:48 by tjmari            #+#    #+#              #
#    Updated: 2021/10/22 09:50:17 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = weapon

SRCS = main.cpp Weapon.cpp HumanA.cpp HumanB.cpp

INCLUDES = Weapon.hpp HumanA.hpp HumanB.hpp

OBJS = main.o Weapon.o HumanA.o HumanB.o

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
