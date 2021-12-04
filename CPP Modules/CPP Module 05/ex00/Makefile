# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 17:34:13 by tjmari            #+#    #+#              #
#    Updated: 2021/10/29 17:34:52 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bureaucrat

INCLUDES = Bureaucrat.hpp

SRCS = main.cpp Bureaucrat.cpp

OBJS = main.o Bureaucrat.o

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
