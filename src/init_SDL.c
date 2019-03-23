/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_SDL.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 00:28:41 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 00:30:02 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		init_SDL(t_data *d)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
	{
		ft_putendl_fd("SDL_Init has failed", 2);
		return (0);
	}
	d->win = SDL_CreateWindow("doom-nukem", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	if (!(d->win))
	{
		ft_putendl_fd("SDL_Create_Window has failed", 2);
		return (-1);
	}
	return (0);
}
