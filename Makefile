# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2017/11/02 17:25:12 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt

CC = gcc

CFLAGS = -Wall -Werror -Wextra

INC_FILES = includes/rt.h

INC = includes/

SRC_DIR = srcs/

SRC = main.c \
	  update_fps.c \
	  update_cam.c \
	  end_of_program.c \
	  matrix.c \
	  test.c \
	  event_cam.c \
	  sdl/sdl_init.c \
	  sdl/sdl_put_pixel.c \
	  sdl/sdl_key.c \
	  sdl/sdl_exit.c \
	  sdl/sdl_update_event.c

OBJ_DIR = objs/

OBJET = $(SRC:.c=.o)

SDL_FLAG = -I SDL2-2.0.5/include SDL2-2.0.5/build/.libs/libSDL2.a -framework Cocoa -framework CoreAudio -framework AudioToolbox -framework ForceFeedback -framework CoreVideo -framework Carbon -framework IOKit -liconv

DIR_LFT = libft/
DIR_VEC = vector/

FLAG_LIB = -lft -lvector

DIR_LIB = libs/

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ_DIR) lib $(addprefix $(OBJ_DIR), $(OBJET))
	@$(CC) -I $(INC) $(addprefix $(OBJ_DIR), $(OBJET)) -L./$(DIR_LIB) $(FLAG_LIB) $(SDL_FLAG) -o $(NAME)

lib:
	@(cd $(DIR_LFT) && $(MAKE))
	@(cd $(DIR_VEC) && $(MAKE))
	@(cp $(DIR_LFT)libft.a $(DIR_LIB))
	@(cp $(DIR_VEC)libvector.a $(DIR_LIB))

$(OBJ_DIR) :
	@mkdir $(DIR_LIB)
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)$(SRC_DIR)
	@mkdir $(OBJ_DIR)$/sdl

$(OBJ_DIR)%.o: $(addprefix $(SRC_DIR), %.c) $(INC_FILES)
	@echo "a"
	$(CC) $(CFLAGS) -I ./$(INC) -o $@ -c $<

clean:
	@echo "Clean rt"
	@(cd $(DIR_LFT) && $(MAKE) clean)
	@(cd $(DIR_VEC) && $(MAKE) clean)
	@/bin/rm -rf $(OBJ_DIR)
	@/bin/rm -rf $(DIR_LIB)

fclean:
	@echo "fClean rt"
	@/bin/rm -rf $(OBJ_DIR)
	@(cd $(DIR_LFT) && $(MAKE) fclean)
	@(cd $(DIR_VEC) && $(MAKE) fclean)
	@/bin/rm -rf $(DIR_LIB)
	@/bin/rm -f $(NAME)

re: fclean all
