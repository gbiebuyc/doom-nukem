/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 00:28:41 by nallani           #+#    #+#             */
/*   Updated: 2019/06/28 15:23:54 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	fix_picnum(t_data *d)
{
	int		i;
	int		name_i;

	i = -1;
	while (++i < d->numwalls)
	{
		name_i = -1;
		while (++name_i < d->nb_textures)
			if (ft_strequ(d->walls[i].texture_name, d->tex_name_list[name_i]))
				d->walls[i].lowerpicnum =
				d->walls[i].middlepicnum =
				d->walls[i].upperpicnum = name_i;
	}
	i = -1;
	while (++i < d->numsectors)
	{
		name_i = -1;
		while (++name_i < d->nb_textures)
		{
			if (ft_strequ(d->sectors[i].floor_texture_name, d->tex_name_list[name_i]))
				d->sectors[i].floorpicnum = name_i;
			if (ft_strequ(d->sectors[i].ceil_texture_name, d->tex_name_list[name_i]))
				d->sectors[i].ceilpicnum = name_i;
		}
	}
}

void	load_projectile_texture(t_data *d, const char *path,
		unsigned short i, unsigned short j)
{
	SDL_Surface *tmp;

	if (!(tmp = SDL_LoadBMP(path)))
	{
		ft_putstr_fd("couldn't find ", 2);
		ft_putendl_fd(path, 2);
		exit(EXIT_FAILURE);
	}
	d->projectile_tex[i][j] = tmp;
}

void	load_weapon_texture(t_data *d, const char *path,
		unsigned short i, unsigned short j)
{
	SDL_Surface *tmp;

	if (!(tmp = SDL_LoadBMP(path)))
	{
		ft_putstr_fd("couldn't find ", 2);
		ft_putendl_fd(path, 2);
		exit(EXIT_FAILURE);
	}
	if (!(d->weapon_tex[i][j] = SDL_ConvertSurfaceFormat(tmp,
					d->screen->format->format, 0)))
		exit(EXIT_FAILURE);
	SDL_FreeSurface(tmp);
}
void	load_monster_texture(t_data *d, const char *path, int i[3]) //i[0] == monster_id & i[1] == state_of_anim | anim & i[2] == orientation
{
	SDL_Surface *tmp;

	if (!(tmp = SDL_LoadBMP(path)))
	{
		ft_putstr_fd("couldn't find ", 2);
		ft_putendl_fd(path, 2);
		exit(EXIT_FAILURE);
	}
	if (!(d->monster_text[i[0]][i[1]][i[2]] = SDL_ConvertSurfaceFormat(tmp,
					d->screen->format->format, 0)))
		exit(EXIT_FAILURE);
	SDL_FreeSurface(tmp);
}

void	tmp_load_file_to_del_monster_2(t_data *d)
{
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/A1.bmp", (int[3]){1, 0, 0});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/A2.bmp", (int[3]){1, 0, 1});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/A3.bmp", (int[3]){1, 0, 2});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/A4.bmp", (int[3]){1, 0, 3});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/A5.bmp", (int[3]){1, 0, 4});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/B1.bmp", (int[3]){1, 1, 0});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/B2.bmp", (int[3]){1, 1, 1});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/B3.bmp", (int[3]){1, 1, 2});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/B4.bmp", (int[3]){1, 1, 3});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/B5.bmp", (int[3]){1, 1, 4});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/C1.bmp", (int[3]){1, 2, 0});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/C2.bmp", (int[3]){1, 2, 1});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/C3.bmp", (int[3]){1, 2, 2});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/C4.bmp", (int[3]){1, 2, 3});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/C5.bmp", (int[3]){1, 2, 4});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/D1.bmp", (int[3]){1, 3, 0});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/D2.bmp", (int[3]){1, 3, 1});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/D3.bmp", (int[3]){1, 3, 2});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/D4.bmp", (int[3]){1, 3, 3});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/walk/D5.bmp", (int[3]){1, 3, 4});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/attack/E1.bmp", (int[3]){1, 4, 0});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/attack/E2.bmp", (int[3]){1, 4, 1});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/attack/E3.bmp", (int[3]){1, 4, 2});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/attack/E4.bmp", (int[3]){1, 4, 3});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/attack/E5.bmp", (int[3]){1, 4, 4});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/attack/F1.bmp", (int[3]){1, 5, 0});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/attack/F2.bmp", (int[3]){1, 5, 1});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/attack/F3.bmp", (int[3]){1, 5, 2});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/attack/F4.bmp", (int[3]){1, 5, 3});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/attack/F5.bmp", (int[3]){1, 5, 4});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/attack/G1.bmp", (int[3]){1, 6, 0});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/attack/G2.bmp", (int[3]){1, 6, 1});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/attack/G3.bmp", (int[3]){1, 6, 2});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/attack/G4.bmp", (int[3]){1, 6, 3});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/attack/G5.bmp", (int[3]){1, 6, 4});
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/death/I0.bmp", (int[3]){1, 13, 0});
	d->monster_text[1][13][1] = d->monster_text[1][13][0];
	d->monster_text[1][13][2] = d->monster_text[1][13][0];
	d->monster_text[1][13][3] = d->monster_text[1][13][0];
	d->monster_text[1][13][4] = d->monster_text[1][13][0];
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/death/J0.bmp", (int[3]){1, 14, 0});
	d->monster_text[1][14][1] = d->monster_text[1][14][0];
	d->monster_text[1][14][2] = d->monster_text[1][14][0];
	d->monster_text[1][14][3] = d->monster_text[1][14][0];
	d->monster_text[1][14][4] = d->monster_text[1][14][0];
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/death/K0.bmp", (int[3]){1, 15, 0});
	d->monster_text[1][15][1] = d->monster_text[1][15][0];
	d->monster_text[1][15][2] = d->monster_text[1][15][0];
	d->monster_text[1][15][3] = d->monster_text[1][15][0];
	d->monster_text[1][15][4] = d->monster_text[1][15][0];
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/death/L0.bmp", (int[3]){1, 16, 0});
	d->monster_text[1][16][1] = d->monster_text[1][16][0];
	d->monster_text[1][16][2] = d->monster_text[1][16][0];
	d->monster_text[1][16][3] = d->monster_text[1][16][0];
	d->monster_text[1][16][4] = d->monster_text[1][16][0];
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/death/M0.bmp", (int[3]){1, 17, 0});
	d->monster_text[1][17][1] = d->monster_text[1][17][0];
	d->monster_text[1][17][2] = d->monster_text[1][17][0];
	d->monster_text[1][17][3] = d->monster_text[1][17][0];
	d->monster_text[1][17][4] = d->monster_text[1][17][0];
	load_monster_texture(d, "./textures/assets/monsters/chargingdemon/death/N0.bmp", (int[3]){1, 18, 0});
	d->monster_text[1][18][1] = d->monster_text[1][18][0];
	d->monster_text[1][18][2] = d->monster_text[1][18][0];
	d->monster_text[1][18][3] = d->monster_text[1][18][0];
	d->monster_text[1][18][4] = d->monster_text[1][18][0];
}

void	init_sdl(t_data *d)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
		err_exit(d, 0, SDL_GetError());
	if (!(d->win = SDL_CreateWindow("doom-nukem", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0)))
		err_exit(d, 1, SDL_GetError());
	if (!(d->screen = SDL_GetWindowSurface(d->win)))
		err_exit(d, 1, SDL_GetError());
	if (SDL_SetRelativeMouseMode(SDL_TRUE) == -1)
		err_exit(d, 2, SDL_GetError());
	d->keys = SDL_GetKeyboardState(NULL);
												tmp_load_file_to_del_monster_2(d);
}
