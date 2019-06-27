# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nallani <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/23 19:47:10 by nallani           #+#    #+#              #
#    Updated: 2019/06/26 00:27:23 by gbiebuyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= doom-nukem

FILES= main \
	   move_monster \
	   draw_hud \
	   draw_hud2 \
	   msg \
	   asset_collision \
	   draw_assets \
	   collision \
	   floceiheight \
	   floceiheight2 \
	   the_end \
	   load_sound \
	   sound \
	   handle_finish \
	   exit \
	   init_sdl \
	   init_monsters \
	   init_projectiles \
	   init_player \
	   loop \
	   events \
	   activate_door \
	   press_e \
	   monster_behaviour \
	   monster_anim_state \
	   reorder_sprite \
	   create_projectile \
	   m16 \
	   player_actions \
	   projectile_collision \
	   blaster_col \
	   update \
	   draw_weapon \
	   color_buffer \
	   render \
	   render_sector \
	   draw_floor \
	   draw_ceil \
	   draw_wall \
	   clip_wall \
	   proj_wall \
	   pixel \
	   getpixel \
	   player_damage \
	   load_map load_assets \
	   inside \
	   utils \
	   jump \
	   inertia \
	   movement \
	   draw_sprite \
	   draw_monster \
	   shade \
	   swap_list \
	   draw_aim_cross \
	   font \
	   vector \
	   vector2 \
	   vector3 \
	   load_monsters_texture \
	   load_weapons_texture


SRC= $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ= $(addprefix obj/, $(addsuffix .o, $(FILES)))

ABS_PATH:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
SDL_SOURCES:=$(ABS_PATH)/SDL
SDL_PATH:=$(ABS_PATH)/SDL/library
SDL_CFG = $(SDL_PATH)/bin/sdl2-config
FT_DIR = libft
INCLUDE = includes 
INCLUDE_FILE_NAMES = common.h struct_doom.h doom_nukem.h
INCLUDE_FILES = $(addprefix $(INCLUDE), $(INCLUDE_FILE_NAMES))
CFLAGS = -Wall -Wextra -Werror -Ofast -I$(INCLUDE) -I$(FT_DIR) `$(SDL_CFG) --cflags` \
		 -Wno-unused-variable -Wno-unused-parameter -g
LDFLAGS = -lm -lpthread -L$(FT_DIR) -lft `$(SDL_CFG) --libs` -fsanitize=address
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
	make -C $(SDL_SOURCES) -j4
	make -C $(SDL_SOURCES) install

SDL_clean:
	make -C $(SDL_SOURCES) clean
	make -C $(SDL_SOURCES) uninstall

SDL_re: SDL_clean SDL

sdl:SDL

sdl_re:SDL_re

sdl_clean:SDL_clean
	
.PHONY: SDL clean fclean re all sdl fast editor
