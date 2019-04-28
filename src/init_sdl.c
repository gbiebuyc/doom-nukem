/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 00:28:41 by nallani           #+#    #+#             */
/*   Updated: 2019/04/30 00:15:33 by gbiebuyc         ###   ########.fr       */
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
	d->keys = SDL_GetKeyboardState(NULL);
}
