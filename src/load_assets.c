/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:04:36 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/09 17:04:37 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		read_posters_data(t_data *d, int f)
{
	int	i;
	int w;
	int h;

	if (read(f, &d->nb_posters, sizeof(int32_t)) < 0)
		return (ft_printf("Error read nb posters.\n"));
	if (!(d->posters =
		(SDL_Surface**)malloc(sizeof(SDL_Surface*) * d->nb_posters)))
		return (ft_printf("malloc fail"));
	i = -1;
	while (++i < d->nb_posters)
	{
		if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
			return (ft_printf("Failed to read posters size\n"));
		if (!(d->posters[i] = SDL_CreateRGBSurfaceWithFormat(
								0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
			return (ft_printf("Failed to allocate posters surface\n"));
		if ((read(f, d->posters[i]->pixels, w * h * 4)) < 0)
			return (ft_printf("Read posters data failed\n"));
	}
	return (0);
}

int		read_monsters_data(t_data *d, int f)
{
	int	i;

	if (read(f, &d->nummonsters, sizeof(uint16_t)) < 0)
		return (ft_printf("Failed to read nummonsters.\n"));
	if (d->nummonsters > 0)
	{
		if (!(d->monsters = (t_monster*)malloc(sizeof(t_monster) *
														d->nummonsters)))
			return (ft_printf("Failed to allocate monster stucture.n"));
		i = -1;
		while (++i < d->nummonsters)
			if (read(f, &d->monsters[i], sizeof(t_monster)) < 0)
				return (ft_printf("Failed to read monsters.\n"));
	}
	return (0);
}
