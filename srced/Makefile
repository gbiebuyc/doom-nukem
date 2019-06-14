# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/29 04:25:11 by gbiebuyc          #+#    #+#              #
#    Updated: 2019/06/02 19:15:53 by gbiebuyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../editor

SRC = main.c \
	ed_bmp_reader.c \
	ed_init_structures.c ed_init_editor.c ed_init_texture.c ed_init_assets.c \
	ed_draw.c ed_draw_assets.c \
	ed_conversion.c \
	ed_pixel.c \
	ed_editor.c ed_editor_functions.c ed_editor_sector.c ed_editor_wall.c \
	ed_editor_assets_handler.c ed_monster_list_manager.c \
	ed_event.c ed_event_keyboard.c ed_event_function.c ed_event_mouse_button.c \
	ed_interface.c ed_interface_functions.c \
	ed_interface_map_list.c ed_interface_select_map.c \
	ed_interface_properties.c ed_interface_properties2.c\
	ed_utils.c \
	ed_door_toggle.c \
	ed_detect_wall.c ed_detect_assets.c \
	ed_read_map.c \
	ed_save_file.c ed_fix_data_to_save.c ed_save_assets.c \
	ed_get_monster_files.c ed_get_animation_files.c \
	ed_font.c

OBJ1 = $(SRC:.c=.o)
OBJ2 = $(OBJ1:../src/%=%)
OBJ = $(addprefix obj/, $(OBJ2))

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

./obj/%.o: ./%.c ./editor.h ../includes/common.h ./bmp_reader.h ./font.h
	@mkdir -p obj
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: all clean fclean re
