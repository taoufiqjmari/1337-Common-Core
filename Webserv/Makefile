NC = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
ORANGE = \033[1;33m

COMPILER = clang++
FLAGS = -Wall -Wextra -Werror -std=c++98

NAME = webserv

INCLUDES = webserv.hpp \
			parser/Parser.hpp \
			parser/Tokenizer.hpp \
			parser/Utils.hpp \
			handler/handler.hpp \
			handle_request_response/Handle_request_response.hpp

SRCS = main.cpp \
		parser/Parser.cpp \
		parser/Tokenizer.cpp \
		parser/Utils.cpp \
		handler/handler.cpp \
		handle_request_response/Handle_request_response.cpp \
		handle_request_response/request.cpp \
		handle_request_response/response.cpp \
		handle_request_response/cgi.cpp

all: $(NAME)

$(NAME): $(INCLUDES) $(SRCS)
	@$(COMPILER) $(FLAGS) $(SRCS) -o $(NAME)
	@echo "$(GREEN)Compilation successful$(NC)"

clean:
	@rm -rf $(NAME).dSYM .vscode
	@echo "$(GREEN)Clean successful$(NC)"

fclean: clean
	@rm -f $(NAME)
	@rm -rf .vscode
	@echo "$(GREEN)Full clean successful$(NC)"

re: fclean all

.PHONY: all clean fclean re
