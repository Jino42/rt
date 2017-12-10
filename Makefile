# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2017/12/10 16:56:26 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt

CC = gcc

CFLAGS = -Wall -Werror -Wextra

INC_FILES = includes/rt.h includes/rt_cl.h includes/matrix.h includes/rt_obj.h includes/rt_sdl.h includes/rt_parse.h

INC = -I includes/ -I libft/includes -I vector/includes/ -I SDL2-2.0.5/include

SRC_DIR = srcs/

SRC = main.c \
	  parse.c \
	  mem_obj.c \
	  update_fps.c \
	  update_cam.c \
	  update_obj.c \
	  end_of_program.c \
	  matrix.c \
	  test.c \
	  event_cam.c \
	  solve_quadratic.c \
	  intersection_sphere.c \
	  intersection_plane.c \
	  intersection_cylinder.c \
	  intersection_paraboloid.c \
	  intersection_paraboloid_hyperbolic.c \
	  intersection_ellipsoid.c \
	  intersection_cone.c \
	  parsing/parse.c \
	  parsing/parse_camera.c \
	  parsing/parse_cone.c \
	  parsing/parse_cylinder.c \
	  parsing/parse_ellipsoid.c \
	  parsing/parse_light.c \
	  parsing/parse_name.c \
	  parsing/parse_paraboloid.c \
	  parsing/parse_plan.c \
	  parsing/parse_push.c \
	  parsing/parse_sphere.c \
	  parsing/parse_tab.c \
	  parsing/parse_tools_1.c \
	  parsing/parse_tools_2.c \
	  parsing/parse_gen.c \
	  parsing/parse_get.c \
	  cl/cl_init.c \
	  cl/cl_end.c \
	  cl/cl_create_buffer.c \
	  cl/cl_check_err.c \
	  sdl/sdl_init.c \
	  sdl/sdl_put_pixel.c \
	  sdl/sdl_key.c \
	  sdl/sdl_exit.c \
	  sdl/sdl_update_event.c

OBJ_DIR = objs/

OBJET = $(SRC:.c=.o)

SDL_FLAG = -I SDL2-2.0.5/include SDL2-2.0.5/build/.libs/libSDL2.a -framework Cocoa -framework CoreAudio -framework AudioToolbox -framework ForceFeedback -framework CoreVideo -framework Carbon -framework IOKit -liconv

FRAMEWORK = -framework OpenGL -framework AppKit -framework Opencl

DIR_LFT = libft/
DIR_VEC = vector/

FLAG_LIB = -lft -lvector

DIR_LIB = libs/

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ_DIR) lib $(addprefix $(OBJ_DIR), $(OBJET))
	@$(CC) $(INC) $(addprefix $(OBJ_DIR), $(OBJET)) -L./$(DIR_LIB) $(FLAG_LIB) $(SDL_FLAG) $(FRAMEWORK) -o $(NAME)

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
	@mkdir $(OBJ_DIR)$/cl
	@mkdir $(OBJ_DIR)$/parsing

$(OBJ_DIR)%.o: $(addprefix $(SRC_DIR), %.c) $(INC_FILES)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@echo "build $<"

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

test:
	make -C tests
