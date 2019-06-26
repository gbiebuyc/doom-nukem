/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_read_map_fix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 23:34:10 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/26 23:34:11 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	fix_sector_picnum(t_data *d)
{
	int				i;
	int				name_i;
	t_texture_data	*lst;

	i = -1;
	while (++i < d->numsectors)
	{
		name_i = -1;
		lst = d->texture_list;
		while (++name_i < d->nb_texture)
		{
			if (ft_strequ(d->sectors[i].floor_texture_name, lst->name))
				d->sectors[i].floorpicnum = name_i;
			if (ft_strequ(d->sectors[i].ceil_texture_name, lst->name))
				d->sectors[i].ceilpicnum = name_i;
			lst = lst->next;
		}
	}
}

void	fix_picnum(t_data *d, t_texture_data *lst)
{
	int				i;
	int				name_i;
	int				poster_i;

	i = -1;
	while (++i < d->numwalls && (name_i = -1) < 0)
	{
		lst = d->texture_list;
		while (++name_i < d->nb_texture && (poster_i = -1) < 0 && lst)
		{
			if (ft_strequ(d->walls[i].texture_name, lst->name))
				d->walls[i].lowerpicnum =
				d->walls[i].middlepicnum =
				d->walls[i].upperpicnum = name_i;
			lst = lst->next;
		}
		lst = d->posters_list;
		while (++poster_i < d->nb_posters && lst)
		{
			if (ft_strequ(d->walls[i].poster_name, lst->name))
				d->walls[i].posterpicnum = poster_i;
			lst = lst->next;
		}
	}
	fix_sector_picnum(d);
}
