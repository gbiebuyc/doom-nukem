# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/29 04:25:11 by gbiebuyc          #+#    #+#              #
#    Updated: 2019/05/04 11:29:23 by gbiebuyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../editor
SRC = main.c \
	  init_sdl.c \
	  ../src/vec2.c \
	  ../src/vec2_2.c \
	  draw.c \
	  pixel.c
OBJ = $(SRC:.c=.o)
FT_DIR = ../libft
SDL_CFG = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))/../SDL/library/bin/sdl2-config
CFLAGS = -Wall -Wextra -Werror -I$(FT_DIR) -I../includes `$(SDL_CFG) --cflags`
LDFLAGS = -lm -L$(FT_DIR) -lft `$(SDL_CFG) --libs`
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all
