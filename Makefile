# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nallani <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/23 19:47:10 by nallani           #+#    #+#              #
#    Updated: 2019/03/23 22:25:31 by nallani          ###   ########.fr        #
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



INC_DIR = ./includes
LIB_DIR = ./libft

CFLAGS = -I $(INC_DIR) -Wall -Wextra -Werror -O3 `$(SDL_PATH)/bin/sdl2-config --cflags`
LDFLAGS = -I $(INC_DIR) -lm -L $(LIB_DIR) -lft -lpthread `$(SDL_PATH)/bin/sdl2-config --libs`

all:$(NAME)

$(NAME):$(OBJ)
	gcc -o $@ $(SRC) $(LDFLAGS)

clean:
	rm -rf $(OBJ)

fclean:clean
	rm -rf $(NAME)

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
	
