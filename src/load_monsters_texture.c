/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_monsters_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 16:46:24 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/12 16:46:25 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int read_anim_death_texture(t_data *d, int f, int *i, int nb_o)
{
	int 	o;
	int 	w;
	int 	h;

	if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
		return (ft_printf("Failed to read death texture size.\n"));
	if (!(d->monster_text[i[0]][i[1]][0] = SDL_CreateRGBSurfaceWithFormat(
			  0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
		return (1);
	if (read(f, d->monster_text[i[0]][i[1]][0]->pixels, w * h * 4) < 0)
		return (ft_printf("Failed to read monster texture.\n"));
	o = 0;
	while (++o < nb_o)
		d->monster_text[i[0]][i[1]][o] = d->monster_text[i[0]][i[1]][0];
	return (0);
}

int read_anim_texture(t_data *d, int f, int *i, int nb_o)
{
	int 	o;
	int 	w;
	int 	h;

	o = -1;
	while (++o < nb_o)
	{
		if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
			return (ft_printf("Failed to read texture size.\n"));
		if (!(d->monster_text[i[0]][i[1]][o] = SDL_CreateRGBSurfaceWithFormat(
				  0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
			return (ft_printf("error\n"));
		if (read(f, d->monster_text[i[0]][i[1]][o]->pixels, w * h * 4) < 0)
			return (ft_printf("Failed to read monster texture.\n"));
	}
	return (0);
}

int load_monsters_texture(t_data *d, int f)
{
	int i;
	int a;
	int nb_orientation;

	i = -1;
	while (++i < 1) // 1 is temporary depend the final number of monsters
	{
		a = -1;
		if (read(f, &nb_orientation, sizeof(int)) < 0)
			return (ft_printf("failed to read nb_orientaiton.\n"));
		while (++a < 7)
			if (read_anim_texture(d, f, (int[2]){i, a}, nb_orientation))
				return (1);
		a = 9;
		while (++a < 19)
			if (read_anim_death_texture(d, f, (int[2]){i, a}, nb_orientation))
				return (1);
	}
	return (0);
}
