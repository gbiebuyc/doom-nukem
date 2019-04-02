/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 00:28:41 by nallani           #+#    #+#             */
/*   Updated: 2019/04/01 20:32:06 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


void	load_textures(t_data *d) // a modifier
{
	if (!(d->texture[0] = SDL_LoadBMP("./textures/south.bmp")))
			err_exit(d, 2, SDL_GetError());
	if (!(d->texture[1] = SDL_LoadBMP("./textures/south.bmp")))
			err_exit(d, 3, SDL_GetError());
	if (!(d->texture[2] = SDL_LoadBMP("./textures/south.bmp")))
			err_exit(d, 4, SDL_GetError());
	if (!(d->texture[3] = SDL_LoadBMP("./textures/south.bmp")))
			err_exit(d, 5, SDL_GetError());
}

void	ft_init_sdl(t_data *d, int width, int length)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
		err_exit(d, 0, SDL_GetError());
	if (!(d->main_win.win = SDL_CreateWindow("doom-nukem", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, width, length, SDL_WINDOW_SHOWN |
					SDL_WINDOW_INPUT_FOCUS)))
		err_exit(d, 1, SDL_GetError());
	if (!(d->main_win.surface = SDL_GetWindowSurface(d->main_win.win)))
		err_exit(d, 1, SDL_GetError());
	load_textures(d);
}
