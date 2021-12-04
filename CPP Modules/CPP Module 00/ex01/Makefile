# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 11:53:07 by tjmari            #+#    #+#              #
#    Updated: 2021/10/20 16:25:06 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = phonebook

SRCS = main.cpp Phonebook.cpp Contact.cpp

OBJS = main.o Phonebook.o Contact.o

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
