/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:39:11 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 00:16:45 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


int		main(int argc, char **argv)
{	
	t_data d;

	argc = 1;
	if (argv == NULL)
		;
	else
		;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
	{
		ft_putendl_fd("SDL_Init has failed", 2);
		exit(EXIT_FAILURE);
	}
	d.win = SDL_CreateWindow("doom-nukem", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	if (!(d.win))
	{
		ft_putendl_fd("SDL_Create_Window has failed", 2);
		exit(EXIT_FAILURE);
	}

	while (getchar() != '\n')
		;
	proper_exit(&d);
}
