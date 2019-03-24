/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:39:11 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 01:20:08 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


int		main(int argc, char **argv)
{	
	t_data d;

	(void)argc;
	(void)argv;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
	{
		ft_putendl_fd("SDL_Init has failed", 2);
		exit(EXIT_FAILURE);
	}
	d.win = SDL_CreateWindow("doom-nukem", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	if (!(d.win))
	{
		ft_putendl_fd("SDL_Create_Window has failed", 2);
		exit(EXIT_FAILURE);
	}
	SDL_Surface	*surface;
	surface = SDL_GetWindowSurface(d.win);
	for(int i = 0; i < 600; i++)
		for(int j = 0; j < 800; j++)
			((uint32_t*)surface->pixels)[i * 800 + j] =
				SDL_MapRGBA(surface->format, 0, (uint8_t)j, (uint8_t)i, 255);
	SDL_UpdateWindowSurface(d.win);
	SDL_Event e;
	while (1)
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				proper_exit(&d);
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				proper_exit(&d);
		}
}
