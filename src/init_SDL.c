/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_SDL.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 00:28:41 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 01:35:19 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		init_sdl(t_data *d, int width, int length)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
	{
		ft_putendl_fd("SDL_Init has failed", 2);
		return (0);
	}
	d->main_win.win = SDL_CreateWindow("doom-nukem", 0,
			0, width, length, SDL_WINDOW_SHOWN | 
			SDL_WINDOW_INPUT_FOCUS);
	if (!(d->main_win.win))
	{
		ft_putendl_fd("SDL_Create_Window has failed", 2);
		return (-1);
	}
	return (0);
}
