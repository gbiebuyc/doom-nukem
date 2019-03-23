# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nallani <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/23 19:47:10 by nallani           #+#    #+#              #
#    Updated: 2019/03/23 22:14:06 by nallani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= doom-nukem

FILES= main

SRC= $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ= $(addprefix obj/, $(addsuffix .o, $(FILES)))


OS=$(shell uname -s)
ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
SDL_SOURCES:=$(ROOT_DIR)/SDL_MAC
SDL_PATH:=$(ROOT_DIR)/SDL_MAC/library



FT_DIR = ./includes

CFLAGS = -I $(FT_DIR) -Wall -Wextra -Werror -O3 `~/SDL/bin/sdl2-config --cflags`
LDFLAGS = -lm -L $(FT_DIR) -lft -lpthread `~/SDL/bin/sdl2-config --libs`

all:$(NAME)

$(NAME):$(OBJ)
	gcc -o $@ $(SRC) $(LDFLAGS)

clean:

fclean:

re:

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
	
