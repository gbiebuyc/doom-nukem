# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nallani <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/23 19:47:10 by nallani           #+#    #+#              #
#    Updated: 2019/03/23 21:22:03 by nallani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= doom-nukem


OS=$(shell uname -s)
ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
SDL_SOURCES:=$(ROOT_DIR)/SDL_MAC
SDL_PATH:=$(ROOT_DIR)/SDL_MAC/library



CFLAGS = -I $(FT_DIR) -Wall -Wextra -Werror -O3 `~/SDL/bin/sdl2-config --cflags`
LDFLAGS = -lm -L $(FT_DIR) -lft -lpthread `~/SDL/bin/sdl2-config --libs`

all:

clean:

fclean:

re:

echo:
	echo $(SDL_path)

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
	
cd:
	cd $(SDL_PATH)
