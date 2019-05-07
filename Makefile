# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nallani <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/23 19:47:10 by nallani           #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2019/05/07 00:54:59 by nallani          ###   ########.fr        #
=======
#    Updated: 2019/05/05 01:05:50 by gbiebuyc         ###   ########.fr        #
>>>>>>> dc424990bf39bd4b8be2441cadc0ab96a8fd3c72
#                                                                              #
# **************************************************************************** #

NAME= doom-nukem

FILES= main \
	   exit \
	   init_sdl \
	   init_monsters \
	   loop \
	   events \
	   update \
	   render \
	   render_sector \
	   draw_floor \
	   draw_wall \
	   clip_wall \
	   pixel \
	   load_map \
	   inside \
	   utils \
<<<<<<< HEAD
	   jump \
	   movement \
	   draw_sprite \
=======
	   shade \
>>>>>>> dc424990bf39bd4b8be2441cadc0ab96a8fd3c72
	   vec2 \
	   vec2_2

SRC= $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ= $(addprefix obj/, $(addsuffix .o, $(FILES)))

ABS_PATH:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
SDL_SOURCES:=$(ABS_PATH)/SDL
SDL_PATH:=$(ABS_PATH)/SDL/library
SDL_CFG = $(SDL_PATH)/bin/sdl2-config
FT_DIR = libft
INCLUDE = includes 
CFLAGS = -Wall -Wextra -Werror -O3 -I$(INCLUDE) -I$(FT_DIR) `$(SDL_CFG) --cflags`
LDFLAGS = -lm -L$(FT_DIR) -lft `$(SDL_CFG) --libs`
ED_DIR = srced

all: $(NAME) editor

#rajouter compilation de libft / autres libs (sdl ?)
$(NAME):$(OBJ)
	make -C libft
	gcc -o $@ $(OBJ) $(LDFLAGS)

editor:
	make -C $(ED_DIR)

clean:
	make -C $(FT_DIR) clean
	make -C $(ED_DIR) clean
	rm -rf $(OBJ)

fclean:
	#make -C $(FT_DIR) fclean // penible a chaque make re
	make -C $(ED_DIR) fclean
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) -o $@ -c $< $(CFLAGS)

#modifier $(NAME) pour compiler la sdl et etre en accord avec le pdf
fast:
	make -C libft
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

#compilation SDL

SDL:
	cd $(SDL_SOURCES); ./configure --prefix=$(SDL_PATH)
	make -C $(SDL_SOURCES)
	make -C $(SDL_SOURCES) install

SDL_clean:
	make -C $(SDL_SOURCES) clean
	make -C $(SDL_SOURCES) uninstall

SDL_re: SDL_clean SDL

sdl:SDL

sdl_re:SDL_re

sdl_clean:SDL_clean
	
.PHONY: SDL clean fclean re all sdl fast editor
