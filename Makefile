# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nallani <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/23 19:47:10 by nallani           #+#    #+#              #
#    Updated: 2019/03/24 04:17:35 by nallani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= doom-nukem

FILES= main \
	   exit \
	   init_SDL \
	   loop \
	   key_event \
	   window_event
#need to reorganize and optimize files (especially loop and events
SRC= $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ= $(addprefix obj/, $(addsuffix .o, $(FILES)))

OS=$(shell uname -s)
ABS_PATH:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
SDL_SOURCES:=$(ABS_PATH)/SDL
SDL_PATH:=$(ABS_PATH)/SDL/library
FT_DIR = ./libft
INCLUDE = -I./includes 

CFLAGS = $(INCLUDE) -Wall -Wextra -Werror -O3 `$(SDL_PATH)/bin/sdl2-config --cflags`
LDFLAGS = -lm -L $(FT_DIR) -lft -lpthread `$(SDL_PATH)/bin/sdl2-config --libs`

all: $(NAME)

#rajouter compilation de libft / autres libs (sdl ?)
$(NAME):$(OBJ)
	make -C libft
	gcc -o $@ $(OBJ) $(LDFLAGS)

clean:
	make -C $(FT_DIR) clean
	rm -rf $(OBJ)

fclean:
	make -C $(FT_DIR) fclean
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all

obj/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)


#compilation SDL

SDL:
	cd $(SDL_SOURCES); ./configure --prefix=$(SDL_PATH)
	make -C $(SDL_SOURCES)
	make -C $(SDL_SOURCES) install

SDL_clean:
	make -C $(SDL_SOURCES) clean
	make -C $(SDL_SOURCES) uninstall

SDL_re: SDL_clean SDL
	
.PHONY: SDL clean fclean re all
