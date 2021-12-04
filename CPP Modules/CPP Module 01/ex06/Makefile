# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 18:13:03 by tjmari            #+#    #+#              #
#    Updated: 2021/10/22 09:12:48 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = karenFilter

SRCS = main.cpp karen.cpp

INCLUDES = karen.hpp

OBJS = main.o

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
