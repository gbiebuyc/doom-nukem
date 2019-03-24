/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:39:11 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 03:07:23 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


int		main(int argc, char **argv)
{	
	t_data d;

	(void)argc;
	(void)argv;
	d.time.ini_time = clock()/CLOCK_PER_SEC;
	d.time.last_time = 0.0;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
	{
		ft_putendl_fd("SDL_Init has failed", 2);
		exit(EXIT_FAILURE);
	}
	d.main_win.win = SDL_CreateWindow("doom-nukem", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	if (!(d.main_win.win))
	{
		ft_putendl_fd("SDL_Create_Window has failed", 2);
		exit(EXIT_FAILURE);
	}
	SDL_Surface	*surface;
	surface = SDL_GetWindowSurface(d.main_win.win);
	for(int i = 0; i < 600; i++)
		for(int j = 0; j < 800; j++)
			((uint32_t*)surface->pixels)[i * 800 + j] =
				SDL_MapRGBA(surface->format, 0, (uint8_t)j, (uint8_t)i, 255);
	SDL_UpdateWindowSurface(d.main_win.win);
	while (1)
		loop(&d);
}
