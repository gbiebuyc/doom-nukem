/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 09:46:07 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/29 09:46:09 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

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
		exit(EXIT_FAILURE);
	if (!(d->win = SDL_CreateWindow("editor", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, W, H, 0)))
		exit(EXIT_FAILURE);
	if (!(d->screen = SDL_GetWindowSurface(d->win)))
		exit(EXIT_FAILURE);
	/*
	load_texture(d, "./textures/north.bmp");
	load_texture(d, "./textures/south.bmp");
	load_texture(d, "./textures/east.bmp");
	load_texture(d, "./textures/west.bmp");
	*/
}
