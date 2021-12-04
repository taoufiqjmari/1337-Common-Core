# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/24 18:25:34 by tjmari            #+#    #+#              #
#    Updated: 2021/10/26 12:19:35 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fragtrap

INCLUDES = ClapTrap.hpp ScavTrap.hpp FragTrap.hpp

SRCS = main.cpp ClapTrap.cpp ScavTrap.cpp FragTrap.cpp

OBJS = main.o ClapTrap.o ScavTrap.o FragTrap.o

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
