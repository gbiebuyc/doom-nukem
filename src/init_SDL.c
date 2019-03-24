/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 00:28:41 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 08:45:50 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_init_sdl(t_data *d, int width, int length)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) && ++d->err_count)
		err_exit(d, d->err_count, SDL_GetError());
	if (!(d->main_win.win = SDL_CreateWindow("doom-nukem", 0,
			0, width, length, SDL_WINDOW_SHOWN |
			SDL_WINDOW_INPUT_FOCUS)) && ++d->err_count)
		err_exit(d, d->err_count, SDL_GetError());
}
