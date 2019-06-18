/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 00:28:41 by nallani           #+#    #+#             */
/*   Updated: 2019/06/07 23:17:34 by nallani          ###   ########.fr       */
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
	d->projectile_tex[i][j] = tmp;
	// if (!(d->projectile_tex[i][j] = SDL_ConvertSurfaceFormat(tmp,
	// 				d->screen->format->format, 0)))
	// 	exit(EXIT_FAILURE);
	//SDL_FreeSurface(tmp);
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

	// proj monster
	load_projectile_texture(d, "./textures/sprites/projectiles/fireball_1/BAL1A0.bmp", FIREBALL_1, 0);
	load_projectile_texture(d, "./textures/sprites/projectiles/fireball_1/BAL1B0.bmp", FIREBALL_1, 1);
	load_projectile_texture(d, "./textures/sprites/projectiles/fireball_1/BAL1C0.bmp", FIREBALL_1, 2);
	load_projectile_texture(d, "./textures/sprites/projectiles/fireball_1/BAL1D0.bmp", FIREBALL_1, 3);
	load_projectile_texture(d, "./textures/sprites/projectiles/fireball_1/BAL1E0.bmp", FIREBALL_1, 4);
	
	d->keys = SDL_GetKeyboardState(NULL);
}
