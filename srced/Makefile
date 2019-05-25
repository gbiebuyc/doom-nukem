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
	  ed_init.c ed_init_texture.c \
	  ../src/vec2.c \
	  ../src/vec2_2.c \
	  ed_draw.c \
	  ed_conversion.c \
	  ed_pixel.c \
	  ed_editor.c ed_editor_functions.c ed_editor_sector.c ed_editor_wall.c \
	  ed_event.c ed_event_function.c ed_event_mouse_button.c \
	  ed_interface.c ed_interface_functions.c \
	  ed_interface_properties.c ed_interface_properties2.c\
	  ed_utils.c \

OBJ = $(SRC:.c=.o)

CC = gcc
#-fsanitize=address

FT_DIR = ../libft
SDL_CFG = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))/../SDL/library/bin/sdl2-config
CFLAGS = -Wall -Wextra -Werror -I$(FT_DIR) -I../includes `$(SDL_CFG) --cflags`
LDFLAGS = -lm -L$(FT_DIR) -lft `$(SDL_CFG) --libs`

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all

./%.o: ./%.c ./editor.h ../includes/common.h
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: all clean fclean re
