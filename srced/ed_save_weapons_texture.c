/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_save_weapons_texture.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 18:15:50 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/16 18:15:51 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

#define WEAP_NAME (char*[]){"cryo_ballista/", "blaster/", "m16/"}
#define NB_TEX (int[3]){13, 15, 3}
#define NB_PROJECTILE (int[3]){20, 0, 5}

static int		save_texture_to_file(t_data *d, int f, int *nb_tex, int *nb_pro)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < nb_tex[i])
			if (write(f, &d->weap_tex[i][j]->w, sizeof(int)) < 0 ||
				write(f, &d->weap_tex[i][j]->h, sizeof(int)) < 0 ||
				write(f, d->weap_tex[i][j]->pixels,
					d->weap_tex[i][j]->w * d->weap_tex[i][j]->h * 4) < 0)
				return (ft_printf("Failed to write texture weapon.\n"));
		j = -1;
		while (++j < nb_pro[i])
			if (write(f, &d->weap_proj[i][j]->w, sizeof(int)) < 0 ||
				write(f, &d->weap_proj[i][j]->h, sizeof(int)) < 0 ||
				write(f, d->weap_proj[i][j]->pixels,
					d->weap_proj[i][j]->w * d->weap_proj[i][j]->h * 4) < 0)
				return (ft_printf("Failed to write texture weapon.\n"));
	}
	return (0);
}

static int		load_weapon_texture(t_data *d, int *nb_tex, int *nb_projectile)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < nb_tex[i])
			if (!(d->weap_tex[i][j] = SDL_LoadBMP(d->weap_list[i][0][j])))
				return (ft_printf("Failed load %s.\n", d->weap_list[i][0][j]));
		j = -1;
		while (++j < nb_projectile[i])
			if (!(d->weap_proj[i][j] = SDL_LoadBMP(d->weap_list[i][1][j])))
				return (ft_printf("Failed load %s.\n", d->weap_list[i][1][j]));
	}
	return (0);
}

int				write_weapons_texture(t_data *d, int f)
{
	static int	check = 0;

	if (!check)
	{
		check = 1;
		if (get_weapons_list(d, WEAP_NAME, NB_TEX, NB_PROJECTILE) ||
			load_weapon_texture(d, NB_TEX, NB_PROJECTILE))
			return (1);
	}
	if (save_texture_to_file(d, f, NB_TEX, NB_PROJECTILE))
		return (1);
	return (0);
}
