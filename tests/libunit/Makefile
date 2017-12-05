# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apachkof <apachkof@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/26 20:20:01 by apachkof          #+#    #+#              #
#    Updated: 2017/11/26 22:43:35 by apachkof         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE ?= make
CC ?= gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -pedantic -g3 -O1
# -fno-omit-frame-pointer -fsanitize=address
CPPFLAGS = -I./includes/
LDLIBS =
LDFLAGS = -Llibft_ntoniolo/
NAME = libunit.a

SRC_FILES = libunit_putnumber.c \
			launch_tests.c \
			redirect_stdout.c \
			load_test.c

SRC_DIR = .

SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILES))

OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRC))

STEAM = \033[1;30m
COFFEE = \033[1;31m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ)
	$(RM) -R $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SUFFIXES:

coffee:
	@echo "        $(STEAM)..\"$(NC)"
	@echo "      $(STEAM)..$(NC)  $(STEAM)..\"$(NC)"
	@echo "            $(STEAM)..\"$(NC)"
	@echo "             $(STEAM)..\"$(NC)"
	@echo "            $(STEAM)..\"$(NC)"
	@echo "           $(STEAM)..\"$(NC)"
	@echo "         $(STEAM)..\"$(NC)"
	@echo "##      $(STEAM)..$(NC)     ####"
	@echo "##$(COFFEE).............$(NC)##  ##"
	@echo "##$(COFFEE).............$(NC)##   ##"
	@echo "##$(COFFEE).............$(NC)## ##"
	@echo "##$(COFFEE).............$(NC)###"
	@echo " ##$(COFFEE)...........$(NC)##"
	@echo "¸ ############# ˛"
	@echo "#################"

depend:
	@sed '/#\{35\} Generated #\{34\}/q' Makefile >> Makefile.new
	@mv Makefile.new Makefile
	@$(foreach source, $(SRC), echo '' >> 'Makefile'; \
		gcc -MM $(source) $(CPPFLAGS) \
		| sed 's/\(^.*\.o\): \(.*\.c\)/$$(OBJ_DIR)\/\1: $$(SRC_DIR)\/\2/' >> 'Makefile'; \
		echo '\t$$(CC)' -c '$(patsubst $(SRC_DIR)/%,$$(SRC_DIR)/%, $(source))' '$$(CFLAGS) $$(CPPFLAGS) \
		-o $(patsubst $(SRC_DIR)/%.c,$$(OBJ_DIR)/%.o, $(source))' >> 'Makefile';)

################################### Generated ##################################

$(OBJ_DIR)/libunit_putnumber.o: $(SRC_DIR)/libunit_putnumber.c
	$(CC) -c $(SRC_DIR)/libunit_putnumber.c $(CFLAGS) $(CPPFLAGS) -o $(OBJ_DIR)/libunit_putnumber.o

$(OBJ_DIR)/launch_tests.o: $(SRC_DIR)/launch_tests.c includes/libunit.h
	$(CC) -c $(SRC_DIR)/launch_tests.c $(CFLAGS) $(CPPFLAGS) -o $(OBJ_DIR)/launch_tests.o

$(OBJ_DIR)/redirect_stdout.o: $(SRC_DIR)/redirect_stdout.c includes/libunit.h
	$(CC) -c $(SRC_DIR)/redirect_stdout.c $(CFLAGS) $(CPPFLAGS) -o $(OBJ_DIR)/redirect_stdout.o

$(OBJ_DIR)/load_test.o: $(SRC_DIR)/load_test.c includes/libunit.h
	$(CC) -c $(SRC_DIR)/load_test.c $(CFLAGS) $(CPPFLAGS) -o $(OBJ_DIR)/load_test.o
