/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 00:28:41 by nallani           #+#    #+#             */
/*   Updated: 2019/06/06 20:05:19 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	load_texture(t_data *d, char *path)
{
	static int	i;
	SDL_Surface *tmp;

	if (!(tmp = SDL_LoadBMP(path)))
		exit(EXIT_FAILURE);
	if (!(d->textures[i++] = SDL_ConvertSurfaceFormat(tmp,
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

void	load_projectile_texture(t_data *d, const char *path, unsigned short i, unsigned short j)
{
	SDL_Surface *tmp;

	if (!(tmp = SDL_LoadBMP(path)))
	{
		ft_putstr_fd("couldn't find ", 2);
		ft_putendl_fd(path, 2);
		exit(EXIT_FAILURE);
	}
	if (!(d->projectile_tex[i][j] = SDL_ConvertSurfaceFormat(tmp,
					d->screen->format->format, 0)))
		exit(EXIT_FAILURE);
	SDL_FreeSurface(tmp);
}

void	load_weapon_texture(t_data *d, const char *path, unsigned short i, unsigned short j)
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
/********************/
	fix_picnum(d);
/********************/
	load_monster_texture(d, "./textures/sprites/motherdemon/walk1_idle/MOMDA1.bmp", (int[3]){0, 0, 0});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk1_idle/MOMDA2A8.bmp", (int[3]){0, 0, 1});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk1_idle/MOMDA3A7.bmp", (int[3]){0, 0, 2});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk1_idle/MOMDA4A6.bmp", (int[3]){0, 0, 3});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk1_idle/MOMDA5.bmp", (int[3]){0, 0, 4});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk2/MOMDB1.bmp", (int[3]){0, 1, 0});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk2/MOMDB2B8.bmp", (int[3]){0, 1, 1});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk2/MOMDB3B7.bmp", (int[3]){0, 1, 2});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk2/MOMDB4B6.bmp", (int[3]){0, 1, 3});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk2/MOMDB5.bmp", (int[3]){0, 1, 4});
	d->monster_text[0][2][0] = d->monster_text[0][0][0];
	d->monster_text[0][2][1] = d->monster_text[0][0][1];
	d->monster_text[0][2][2] = d->monster_text[0][0][2];
	d->monster_text[0][2][3] = d->monster_text[0][0][3];
	d->monster_text[0][2][4] = d->monster_text[0][0][4];
	load_monster_texture(d, "./textures/sprites/motherdemon/walk3/MOMDD1.bmp", (int[3]){0, 3, 0});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk3/MOMDD2D8.bmp", (int[3]){0, 3, 1});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk3/MOMDD3D7.bmp", (int[3]){0, 3, 2});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk3/MOMDD4D6.bmp", (int[3]){0, 3, 3});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk3/MOMDD5.bmp", (int[3]){0, 3, 4});
	//monster part
	//motherdemon part
	// walking anim and idle part
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/walk1_idle/MOMDA1.bmp", (int[3]){MOTHERDEMON, 0, 0});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/walk1_idle/MOMDA2A8.bmp", (int[3]){MOTHERDEMON, 0, 1});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/walk1_idle/MOMDA3A7.bmp", (int[3]){MOTHERDEMON, 0, 2});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/walk1_idle/MOMDA4A6.bmp", (int[3]){MOTHERDEMON, 0, 3});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/walk1_idle/MOMDA5.bmp", (int[3]){MOTHERDEMON, 0, 4});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/walk2/MOMDB1.bmp", (int[3]){MOTHERDEMON, 1, 0});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/walk2/MOMDB2B8.bmp", (int[3]){MOTHERDEMON, 1, 1});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/walk2/MOMDB3B7.bmp", (int[3]){MOTHERDEMON, 1, 2});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/walk2/MOMDB4B6.bmp", (int[3]){MOTHERDEMON, 1, 3});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/walk2/MOMDB5.bmp", (int[3]){MOTHERDEMON, 1, 4});
	d->monster_text[MOTHERDEMON][2][0] = d->monster_text[MOTHERDEMON][0][0];
	d->monster_text[MOTHERDEMON][2][1] = d->monster_text[MOTHERDEMON][0][1];
	d->monster_text[MOTHERDEMON][2][2] = d->monster_text[MOTHERDEMON][0][2];
	d->monster_text[MOTHERDEMON][2][3] = d->monster_text[MOTHERDEMON][0][3];
	d->monster_text[MOTHERDEMON][2][4] = d->monster_text[MOTHERDEMON][0][4];
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/walk3/MOMDD1.bmp", (int[3]){MOTHERDEMON, 3, 0});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/walk3/MOMDD2D8.bmp", (int[3]){MOTHERDEMON, 3, 1});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/walk3/MOMDD3D7.bmp", (int[3]){MOTHERDEMON, 3, 2});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/walk3/MOMDD4D6.bmp", (int[3]){MOTHERDEMON, 3, 3});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/walk3/MOMDD5.bmp", (int[3]){MOTHERDEMON, 3, 4});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/attack_1_1/MOMDE1.bmp", (int[3]){MOTHERDEMON, 4, 0});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/attack_1_1/MOMDE2E8.bmp", (int[3]){MOTHERDEMON, 4, 1});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/attack_1_1/MOMDE3E7.bmp", (int[3]){MOTHERDEMON, 4, 2});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/attack_1_1/MOMDE4E6.bmp", (int[3]){MOTHERDEMON, 4, 3});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/attack_1_1/MOMDE5.bmp", (int[3]){MOTHERDEMON, 4, 4});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/attack_1_2/MOMDF1.bmp", (int[3]){MOTHERDEMON, 5, 0});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/attack_1_2/MOMDF2F8.bmp", (int[3]){MOTHERDEMON, 5, 1});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/attack_1_2/MOMDF3F7.bmp", (int[3]){MOTHERDEMON, 5, 2});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/attack_1_2/MOMDF4F6.bmp", (int[3]){MOTHERDEMON, 5, 3});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/attack_1_2/MOMDF5.bmp", (int[3]){MOTHERDEMON, 5, 4});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/attack_1_3/MOMDG1.bmp", (int[3]){MOTHERDEMON, 6, 0});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/attack_1_3/MOMDG2G8.bmp", (int[3]){MOTHERDEMON, 6, 1});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/attack_1_3/MOMDG3G7.bmp", (int[3]){MOTHERDEMON, 6, 2});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/attack_1_3/MOMDG4G6.bmp", (int[3]){MOTHERDEMON, 6, 3});
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/attack_1_3/MOMDG5.bmp", (int[3]){MOTHERDEMON, 6, 4});
	// death part
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/death/MOMDL0.bmp", (int[3]){MOTHERDEMON, 10, 0});
	d->monster_text[MOTHERDEMON][10][1] = d->monster_text[MOTHERDEMON][10][0];
	d->monster_text[MOTHERDEMON][10][2] = d->monster_text[MOTHERDEMON][10][0];
	d->monster_text[MOTHERDEMON][10][3] = d->monster_text[MOTHERDEMON][10][0];
	d->monster_text[MOTHERDEMON][10][4] = d->monster_text[MOTHERDEMON][10][0];
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/death/MOMDM0.bmp", (int[3]){MOTHERDEMON, 11, 0});
	d->monster_text[MOTHERDEMON][11][1] = d->monster_text[MOTHERDEMON][11][0];
	d->monster_text[MOTHERDEMON][11][2] = d->monster_text[MOTHERDEMON][11][0];
	d->monster_text[MOTHERDEMON][11][3] = d->monster_text[MOTHERDEMON][11][0];
	d->monster_text[MOTHERDEMON][11][4] = d->monster_text[MOTHERDEMON][11][0];
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/death/MOMDN0.bmp", (int[3]){MOTHERDEMON, 12, 0});
	d->monster_text[MOTHERDEMON][12][1] = d->monster_text[MOTHERDEMON][12][0];
	d->monster_text[MOTHERDEMON][12][2] = d->monster_text[MOTHERDEMON][12][0];
	d->monster_text[MOTHERDEMON][12][3] = d->monster_text[MOTHERDEMON][12][0];
	d->monster_text[MOTHERDEMON][12][4] = d->monster_text[MOTHERDEMON][12][0];
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/death/MOMDO0.bmp", (int[3]){MOTHERDEMON, 13, 0});
	d->monster_text[MOTHERDEMON][13][1] = d->monster_text[MOTHERDEMON][13][0];
	d->monster_text[MOTHERDEMON][13][2] = d->monster_text[MOTHERDEMON][13][0];
	d->monster_text[MOTHERDEMON][13][3] = d->monster_text[MOTHERDEMON][13][0];
	d->monster_text[MOTHERDEMON][13][4] = d->monster_text[MOTHERDEMON][13][0];
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/death/MOMDP0.bmp", (int[3]){MOTHERDEMON, 14, 0});
	d->monster_text[MOTHERDEMON][14][1] = d->monster_text[MOTHERDEMON][14][0];
	d->monster_text[MOTHERDEMON][14][2] = d->monster_text[MOTHERDEMON][14][0];
	d->monster_text[MOTHERDEMON][14][3] = d->monster_text[MOTHERDEMON][14][0];
	d->monster_text[MOTHERDEMON][14][4] = d->monster_text[MOTHERDEMON][14][0];
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/death/MOMDQ0.bmp", (int[3]){MOTHERDEMON, 15, 0});
	d->monster_text[MOTHERDEMON][15][1] = d->monster_text[MOTHERDEMON][15][0];
	d->monster_text[MOTHERDEMON][15][2] = d->monster_text[MOTHERDEMON][15][0];
	d->monster_text[MOTHERDEMON][15][3] = d->monster_text[MOTHERDEMON][15][0];
	d->monster_text[MOTHERDEMON][15][4] = d->monster_text[MOTHERDEMON][15][0];
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/death/MOMDR0.bmp", (int[3]){MOTHERDEMON, 16, 0});
	d->monster_text[MOTHERDEMON][16][1] = d->monster_text[MOTHERDEMON][16][0];
	d->monster_text[MOTHERDEMON][16][2] = d->monster_text[MOTHERDEMON][16][0];
	d->monster_text[MOTHERDEMON][16][3] = d->monster_text[MOTHERDEMON][16][0];
	d->monster_text[MOTHERDEMON][16][4] = d->monster_text[MOTHERDEMON][16][0];
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/death/MOMDS0.bmp", (int[3]){MOTHERDEMON, 17, 0});
	d->monster_text[MOTHERDEMON][17][1] = d->monster_text[MOTHERDEMON][17][0];
	d->monster_text[MOTHERDEMON][17][2] = d->monster_text[MOTHERDEMON][17][0];
	d->monster_text[MOTHERDEMON][17][3] = d->monster_text[MOTHERDEMON][17][0];
	d->monster_text[MOTHERDEMON][17][4] = d->monster_text[MOTHERDEMON][17][0];
	load_monster_texture(d, "./textures/sprites/monsters/motherdemon/death/MOMDT0.bmp", (int[3]){MOTHERDEMON, 18, 0});
	d->monster_text[MOTHERDEMON][18][1] = d->monster_text[MOTHERDEMON][18][0];
	d->monster_text[MOTHERDEMON][18][2] = d->monster_text[MOTHERDEMON][18][0];
	d->monster_text[MOTHERDEMON][18][3] = d->monster_text[MOTHERDEMON][18][0];
	d->monster_text[MOTHERDEMON][18][4] = d->monster_text[MOTHERDEMON][18][0];
	//projectile part
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BSHTA0.bmp", CRYO_BALLISTA, 0);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BSHTB0.bmp", CRYO_BALLISTA, 1);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BSHTC0.bmp", CRYO_BALLISTA, 2);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BSHTD0.bmp", CRYO_BALLISTA, 3);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BSHTE0.bmp", CRYO_BALLISTA, 4);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BSHTF0.bmp", CRYO_BALLISTA, 5);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BSHTG0.bmp", CRYO_BALLISTA, 6);

	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BXPLA0.bmp", CRYO_BALLISTA, 7);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BXPLB0.bmp", CRYO_BALLISTA, 8);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BXPLC0.bmp", CRYO_BALLISTA, 9);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BXPLD0.bmp", CRYO_BALLISTA, 10);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BXPLE0.bmp", CRYO_BALLISTA, 11);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BXPLF0.bmp", CRYO_BALLISTA, 12);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BXPLG0.bmp", CRYO_BALLISTA, 13);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BXPLH0.bmp", CRYO_BALLISTA, 14);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BXPLI0.bmp", CRYO_BALLISTA, 15);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BXPLJ0.bmp", CRYO_BALLISTA, 16);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BXPLK0.bmp", CRYO_BALLISTA, 17);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BXPLL0.bmp", CRYO_BALLISTA, 18);
	load_projectile_texture(d, "./textures/sprites/projectiles/cryo_ballista/BXPLM0.bmp", CRYO_BALLISTA, 19);
	// proj monster
	load_projectile_texture(d, "./textures/sprites/projectiles/fireball_1/BAL1A0.bmp", FIREBALL_1, 0);
	load_projectile_texture(d, "./textures/sprites/projectiles/fireball_1/BAL1B0.bmp", FIREBALL_1, 1);
	load_projectile_texture(d, "./textures/sprites/projectiles/fireball_1/BAL1C0.bmp", FIREBALL_1, 2);
	load_projectile_texture(d, "./textures/sprites/projectiles/fireball_1/BAL1D0.bmp", FIREBALL_1, 3);
	load_projectile_texture(d, "./textures/sprites/projectiles/fireball_1/BAL1E0.bmp", FIREBALL_1, 4);
	// weapon part
	// cryoballista
	load_weapon_texture(d, "./textures/sprites/weapons/cryo_ballista/BSTAA0.bmp", CRYO_BALLISTA, 0);
	load_weapon_texture(d, "./textures/sprites/weapons/cryo_ballista/BSTAB0.bmp", CRYO_BALLISTA, 1);
	load_weapon_texture(d, "./textures/sprites/weapons/cryo_ballista/BSTAC0.bmp", CRYO_BALLISTA, 2);
	load_weapon_texture(d, "./textures/sprites/weapons/cryo_ballista/BSTAD0.bmp", CRYO_BALLISTA, 3);
	load_weapon_texture(d, "./textures/sprites/weapons/cryo_ballista/BSTAE0.bmp", CRYO_BALLISTA, 4);
	load_weapon_texture(d, "./textures/sprites/weapons/cryo_ballista/BSTAF0.bmp", CRYO_BALLISTA, 5);
	load_weapon_texture(d, "./textures/sprites/weapons/cryo_ballista/BSTAG0.bmp", CRYO_BALLISTA, 6);
	load_weapon_texture(d, "./textures/sprites/weapons/cryo_ballista/BSTAH0.bmp", CRYO_BALLISTA, 7);
	load_weapon_texture(d, "./textures/sprites/weapons/cryo_ballista/BSTAI0.bmp", CRYO_BALLISTA, 8);
	load_weapon_texture(d, "./textures/sprites/weapons/cryo_ballista/BSTAJ0.bmp", CRYO_BALLISTA, 9);
	load_weapon_texture(d, "./textures/sprites/weapons/cryo_ballista/BSTAK0.bmp", CRYO_BALLISTA, 10);
	load_weapon_texture(d, "./textures/sprites/weapons/cryo_ballista/BSTAL0.bmp", CRYO_BALLISTA, 11);
	load_weapon_texture(d, "./textures/sprites/weapons/cryo_ballista/BSTAM0.bmp", CRYO_BALLISTA, 12);
	// blaster
	load_weapon_texture(d, "./textures/sprites/weapons/blaster/BG2GA0.bmp", BLASTER, 0);
	load_weapon_texture(d, "./textures/sprites/weapons/blaster/BG2GB0.bmp", BLASTER, 1);
	load_weapon_texture(d, "./textures/sprites/weapons/blaster/BG2GC0.bmp", BLASTER, 2);
	load_weapon_texture(d, "./textures/sprites/weapons/blaster/BG2GD0.bmp", BLASTER, 3);
	load_weapon_texture(d, "./textures/sprites/weapons/blaster/BG2GE0.bmp", BLASTER, 4);
	load_weapon_texture(d, "./textures/sprites/weapons/blaster/BG2GF0.bmp", BLASTER, 5);
	load_weapon_texture(d, "./textures/sprites/weapons/blaster/BG2GG0.bmp", BLASTER, 6);
	load_weapon_texture(d, "./textures/sprites/weapons/blaster/BG2GH0.bmp", BLASTER, 7);
	load_weapon_texture(d, "./textures/sprites/weapons/blaster/BG2GI0.bmp", BLASTER, 8);
	load_weapon_texture(d, "./textures/sprites/weapons/blaster/BG2GJ0.bmp", BLASTER, 9);
	load_weapon_texture(d, "./textures/sprites/weapons/blaster/BG2GK0.bmp", BLASTER, 10);
	load_weapon_texture(d, "./textures/sprites/weapons/blaster/BG2GL0.bmp", BLASTER, 11);
	load_weapon_texture(d, "./textures/sprites/weapons/blaster/BG2GM0.bmp", BLASTER, 12);
	load_weapon_texture(d, "./textures/sprites/weapons/blaster/BG2GN0.bmp", BLASTER, 13);
	load_weapon_texture(d, "./textures/sprites/weapons/blaster/BG2GO0.bmp", BLASTER, 14);

	d->keys = SDL_GetKeyboardState(NULL);
}
