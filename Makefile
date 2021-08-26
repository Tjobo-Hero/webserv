# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: renebraaksma <renebraaksma@student.42.f      +#+                      #
#                                                    +#+                       #
#    Created: 2021/07/06 14:47:26 by rbraaksm      #+#    #+#                  #
#    Updated: 2021/08/26 10:24:42 by rbraaksm      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Colours
DARK_GREEN	= \033[0;32m
GREEN		= \033[0;92m
RED			= \033[0;31m
YELLOW		= \033[0;33m
PURPLE		= \033[1;95m
END			= \033[0;0m

PREFIX		= $(DARK_GREEN)$(NAME) $(END)\xc2\xbb

NAME 		= webserv

CXX 		= clang++
CXXFLAGS 	+= -Wall -Werror -Wextra
LDFLAGS 	+=

OBJDIR = obj
SRCDIR = ./srcs/

FILES = ./srcs/main \
		./srcs/Parser/ConfigParser \
		./srcs/CGI \
		./srcs/Connection \
		./srcs/getPath \
		./srcs/Location \
		./srcs/Request \
		./srcs/Response \
		./srcs/ResponseHeader \
		./srcs/Server \
		./srcs/ServerCluster/ServerCluster\
		./srcs/Utils/base64_decode \
		./srcs/Utils/freeArray \
		./srcs/Utils/getTime \
		./srcs/Utils/signalHandler \
		./srcs/UsersAndPasswords \
		./srcs/Utils/checkLocationPath \
		./srcs/Utils/skipEmptyLine \
		./srcs/Utils/removeSpacesBeforeAfter \
		./srcs/Utils/findFirstWord \
		./srcs/Utils/createParameter \
		./srcs/Utils/getKeyValue \
		./srcs/Utils/getLinesFromTextFile \
		./srcs/Utils/deleteEmptyLines \
		./srcs/Utils/removeComments \
		./srcs/Utils/deleteSpacesBeforeAndAfter \
		./srcs/Utils/checkBrackets \
		./srcs/Utils/textFile \
		./srcs/Utils/checkEndOfLineForSemicolon \
		./srcs/Utils/createSocket \
		./srcs/Utils/setDataStructureToZero \
		./srcs/Utils/setSocketOption \
		./srcs/Utils/bindSocket \
		./srcs/Utils/listenSocket \
		./srcs/ServerCluster/Utils/makeReadyForListening \
		# ./srcs/Utils/print \

SRC = $(addsuffix .cpp, $(FILES))
OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR)/%.o: %.cpp
	@echo "$(PREFIX)$(GREEN) compiling file $(END)$< $(GREEN)into $(END)$@"
	@mkdir -p '$(@D)'
	@$(CXX) -c $(CXXFLAGS) $< -o $@

$(NAME): $(OBJ)
	@echo "\n$(PREFIX)$(GREEN) Executable$(RED) $(NAME)$(GREEN) build$(END)"
	@$(CXX) $^ $(LDFLAGS) -o $(NAME)

test: # OS test
	@echo $(ECHO) "$(PURPLE)Running test \n $(END)"
	@bash -c "cd ./tests && bash run_OS_tester.sh"

clean:
	@echo $(ECHO) "$(PREFIX)$(GREEN) Removing obj directory $(END)$(OUT_DIR)"
	@rm -rf $(OBJDIR)
	@rm -f tests/html_pages/Downloads/Download_* tests/html_pages/Downloads/file_should_exist_after tests/html_pages/Downloads/multiple_same

fclean: clean
	@echo $(ECHO) "$(PREFIX)$(GREEN) Removing executable $(END)$(OUT_DIR)"
	@rm -rf $(NAME)
	@rm -rf ./tests/YoupiBanane
	@rm -rf ./tests/Logs

re: fclean all

.PHONY: clean fclean re all