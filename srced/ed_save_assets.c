/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_save_assets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 21:34:05 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/22 21:34:06 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	clear_assets_structure(t_data *d)
{
	static int	numsect = 0;
	int			s;

	if (!numsect)
		numsect = d->numsectors;
	if (!d->assets)
		return ;
	s = -1;
	while (++s < numsect)
		free(d->assets[s]);
	free(d->assets);
	d->assets = NULL;
	numsect = d->numsectors;
}

void	copy_data(t_data *d, t_assets_list *a, int s, int *i)
{
	d->assets[s][*i].picnum = a->picnum;
	d->assets[s][*i].world_pos = a->world_pos;
	d->assets[s][*i].is_on_ceil = a->is_on_ceil;
	d->assets[s][*i].is_on_floor = a->is_on_floor;
	d->assets[s][*i].stat_mod = a->stat_mod;
	d->assets[s][*i].is_interactive = a->is_interactive;
	d->assets[s][*i].is_autopick = a->is_autopick;
	d->assets[s][*i].collision = a->collision;
	d->assets[s][*i].is_jetpack = a->is_jetpack;
	d->assets[s][*i].is_key = a->is_key;
	d->assets[s][*i].key_num = a->key_num;
	d->assets[s][*i].used = false;
	(*i)++;
}

int		fill_assets_structure(t_data *d)
{
	int				s;
	int				i;
	t_assets_list	*lst;

	clear_assets_structure(d);
	if (!(d->assets = (t_assets**)malloc(sizeof(t_assets*) * d->numsectors)))
		return (ft_printf("Failed to malloc assets structures.\n"));
	s = -1;
	if (!d->interface.assets_list)
		return (0);
	while (++s < d->numsectors && (i = 0) != -1)
	{
		if (!(d->assets[s] = (t_assets*)malloc(sizeof(t_assets) * 10)))
			return (ft_printf("Failed to malloc assets structures.\n"));
		ft_memset(d->assets[s], 0, 10);
		lst = d->interface.assets_list->begin;
		while (i < 10 && lst)
		{
			if (lst->sectnunm == s)
				copy_data(d, lst, s, &i);
			lst = lst->next;
		}
		d->assets[s][0].nb_assets = i;
	}
	return (0);
}

int		write_assets_texture(t_data *d, int f)
{
	int	i;
	int	w;
	int	h;

	if (write(f, &d->interface.nb_asset[0], sizeof(int16_t)) < 0)
		return (ft_printf("Failed to write nb_assets_texture.\n"));
	if (d->interface.nb_asset[0] <= 0)
		return (0);
	i = -1;
	while (++i < d->interface.nb_asset[0])
	{
		w = d->interface.toolbar.assets[0][i]->w;
		h = d->interface.toolbar.assets[0][i]->h;
		if (write(f, &w, sizeof(int)) < 0 || write(f, &h, sizeof(int)) < 0 ||
			write(f, d->interface.toolbar.assets[0][i]->pixels, w * h * 4) < 0)
			return (ft_printf("Failed to write asset texture %d.\n", i));
	}
	return (0);
}

int		write_assets_data(t_data *d, int f)
{
	int	i;
	int	s;

	if (write(f, &d->nb_assets, sizeof(int16_t)) < 0)
		return (ft_printf("Failed to write nb_assets.\n"));
	if (d->nb_assets > 0)
	{
		if (fill_assets_structure(d))
			return (1);
		s = -1;
		while (++s < d->numsectors)
		{
			if (write(f, &d->assets[s][0].nb_assets, sizeof(int)) < 0)
				return (ft_printf("Failed to write nb_assets for sector.\n"));
			i = -1;
			while (++i < d->assets[s][0].nb_assets)
				if (write(f, &d->assets[s][i], sizeof(t_assets)) < 0)
					return (ft_printf("Failed to write d->asset[][].\n"));
		}
	}
	return (0);
}
