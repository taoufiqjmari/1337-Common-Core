# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 17:34:13 by tjmari            #+#    #+#              #
#    Updated: 2021/10/30 19:25:39 by tjmari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = forms

INCLUDES = Bureaucrat.hpp Form.hpp \
		PresidentialPardonForm.hpp RobotomyRequestForm.hpp ShrubberyCreationForm.hpp

SRCS = main.cpp Bureaucrat.cpp Form.cpp \
		PresidentialPardonForm.cpp RobotomyRequestForm.cpp ShrubberyCreationForm.cpp

OBJS = main.o Bureaucrat.o PresidentialPardonForm.o RobotomyRequestForm.o ShrubberyCreationForm.o

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
