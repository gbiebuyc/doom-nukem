/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 00:28:41 by nallani           #+#    #+#             */
/*   Updated: 2019/07/04 14:15:24 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	fix_picnum2(t_data *d)
{
	int		i;
	int		name_i;

	i = -1;
	while (++i < d->numsectors)
	{
		name_i = -1;
		while (++name_i < d->nb_textures)
		{
			if (ft_strequ(d->sectors[i].floor_texture_name,
						d->tex_name_list[name_i]))
				d->sectors[i].floorpicnum = name_i;
			if (ft_strequ(d->sectors[i].ceil_texture_name,
						d->tex_name_list[name_i]))
				d->sectors[i].ceilpicnum = name_i;
		}
	}
}

void	fix_picnum(t_data *d)
{
	int		i;
	int		name_i;

	i = -1;
	while (++i < d->numwalls)
	{
		name_i = -1;
		while (++name_i < d->nb_textures)
			if (ft_strequ(d->walls[i].texture_name, d->tex_name_list[name_i]))
				d->walls[i].lowerpicnum =
				d->walls[i].middlepicnum =
				d->walls[i].upperpicnum = name_i;
	}
	fix_picnum2(d);
}

void	init_sdl(t_data *d)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
		err_exit(SDL_GetError());
	if (!(d->win = SDL_CreateWindow("doom-nukem", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0)))
		err_exit(SDL_GetError());
	if (!(d->screen = SDL_GetWindowSurface(d->win)))
		err_exit(SDL_GetError());
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		err_exit(SDL_GetError());
	if (!Mix_AllocateChannels(MAX_CHANNELS))
		err_exit(SDL_GetError());
	d->keys = SDL_GetKeyboardState(NULL);
}
