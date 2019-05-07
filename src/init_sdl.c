/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 00:28:41 by nallani           #+#    #+#             */
/*   Updated: 2019/05/07 08:45:52 by nallani          ###   ########.fr       */
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

void	load_monster_texture(t_data *d, char *path, bool inc) // pass path for each animation for a monster, once you're done and ready to start a new monster set inc to true instead to false
{
	static int	i;
	static int	j;
	SDL_Surface *tmp;

	if (inc)
	{
		i++;
		j = 0;
	}
	if (!(tmp = SDL_LoadBMP(path)))
		exit(EXIT_FAILURE);
	if (!(d->monster_text[i][j++] = SDL_ConvertSurfaceFormat(tmp,
					d->screen->format->format, 0)))
		exit(EXIT_FAILURE);
//	printf("%d\n", (int)((int32_t*)d->monster_text[0][0]->pixels)[0]); (wtf color ?)
//	printf("%d\n", (int)((int8_t*)d->monster_text[0][0]->pixels)[0]);
//	printf("%d\n", (int)((int8_t*)d->monster_text[0][0]->pixels)[1]);
//	printf("%d\n", (int)((int8_t*)d->monster_text[0][0]->pixels)[2]);
//	printf("%d\n",(int)((int8_t*)d->monster_text[0][0]->pixels)[3]);
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
	load_texture(d, "./textures/north.bmp");
	load_texture(d, "./textures/south.bmp");
	load_texture(d, "./textures/east.bmp");
	load_texture(d, "./textures/west.bmp");
	load_monster_texture(d, "./textures/sprites/motherdemon/walk1/MOMDA1.bmp", false);
	load_monster_texture(d, "./textures/sprites/motherdemon/walk1/MOMDA2A8.bmp", false);
	load_monster_texture(d, "./textures/sprites/motherdemon/walk1/MOMDA3A7.bmp", false);
	load_monster_texture(d, "./textures/sprites/motherdemon/walk1/MOMDA4A6.bmp", false);
	load_monster_texture(d, "./textures/sprites/motherdemon/walk1/MOMDA5.bmp", false);
	d->keys = SDL_GetKeyboardState(NULL);
}
