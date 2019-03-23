# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nallani <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/23 19:47:10 by nallani           #+#    #+#              #
#    Updated: 2019/03/24 00:03:29 by nallani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= doom-nukem

FILES= main \
	   exit

SRC= $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ= $(addprefix obj/, $(addsuffix .o, $(FILES)))


OS=$(shell uname -s)
ABS_PATH:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
SDL_SOURCES:=$(ABS_PATH)/SDL
SDL_PATH:=$(ABS_PATH)/SDL/library



INCLUDE = -I./includes -I./libft -I./SDL/library/include/SDL2
LIB_DIR = ./libft

CFLAGS = $(INCLUDE) -Wall -Wextra -Werror -O3 `$(SDL_PATH)/bin/sdl2-config --cflags`
LDFLAGS = $(INCLUDE) -lm -L $(LIB_DIR) -lft -lpthread `$(SDL_PATH)/bin/sdl2-config --libs`

all:$(NAME)

#rajouter compilation de libt / autres libs
$(NAME):$(OBJ)
	gcc -o $@ $(SRC) $(LDFLAGS)

clean:
	rm -rf $(OBJ)

fclean:clean
	rm -rf $(NAME)

re:fclean clean

$(OBJ):$(SRC)
	gcc -o $@ -c $< $(CFLAGS)





#compilation SDL

ifeq ($(OS), Darwin)
SDL:
	pushd $(SDL_SOURCES) && ./configure --prefix=$(SDL_PATH) && popd
	make -C $(SDL_SOURCES)
	make -C $(SDL_SOURCES) install
else 
ifeq ($(OS), Linux)
SDL:
	@echo "do linux SDL"
else
SDL:
	@echo $(OS) not supported ou window ou jsaispasquoi
endif
endif

SDL_clean:
	make -C $(SDL_SOURCES) clean
	make -C $(SDL_SOURCES) uninstall

SDL_re:SDL_clean SDL
	
.PHONY: SDL clean fclean re all
