# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2017/12/08 18:59:36 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = tests_rt
NAME_LIB_TESTED =
DIR_LIB_TESTED = ../
DIR_FRAMEWORK = ./libunit/

DIR_LIBFT = ../libft/

CC = gcc

CFLAGS = -Wall -Werror -Wextra

CPPFLAGS_FILES = includes/tests_rt.h

CPPFLAGS = -I includes/ -I $(DIR_FRAMEWORK)/includes/ -I $(DIR_LIB_TESTED)includes/ -I $(DIR_LIBFT)includes/

LDLIBS = -lft -lunit

LDFLAGS = -L $(DIR_FRAMEWORK)/ -L $(DIR_LIBFT) -L $(DIR_LIB_TESTED)

SRC_DIR =

SRC = main.c \
tests_gen/00_tests_gen_launcher.c \
tests_camera/00_tests_camera_launcher.c \
tests_light/00_tests_light_launcher.c \
tests_obj_ccp/00_tests_obj_ccp_launcher.c

OBJ_DIR = objs/

OBJET = $(SRC:.c=.o)


.PHONY: all, clean, fclean, re, test

all: $(NAME)

$(NAME): $(OBJ_DIR) lib $(addprefix $(OBJ_DIR), $(OBJET))
	@$(CC) $(CPPFLAGS) $(addprefix $(OBJ_DIR), $(OBJET)) $(LDLIBS) $(LDFLAGS) $(FRAMEWORK) -o $(NAME)
	./$(NAME) $(ARGV)

lib:
	@(make -C $(DIR_FRAMEWORK))
	@(make -C $(DIR_LIBFT))
	@(make -C $(DIR_LIB_TESTED))

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)tests_gen
	@mkdir $(OBJ_DIR)tests_camera
	@mkdir $(OBJ_DIR)tests_light
	@mkdir $(OBJ_DIR)tests_obj_ccp

$(OBJ_DIR)%.o: $(addprefix $(SRC_DIR), %.c) $(CPPFLAGS_FILES)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	@echo "Clean tests rt"
	@(make clean -C $(DIR_LIB_TESTED))
	@/bin/rm -rf $(OBJ_DIR)

fclean:
	@echo "fClean tests rt"
	@/bin/rm -rf $(OBJ_DIR)
	@(make fclean -C $(DIR_LIB_TESTED))
	@/bin/rm -f $(NAME)

re: fclean all
