/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorder_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 00:15:00 by nallani           #+#    #+#             */
/*   Updated: 2019/06/25 22:19:18 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	super_unoptimized_reorder_sprite(t_data *d, t_sector *sec,
		double *vla)
{
	double			tmp_dist;
	t_sprite_list	*mainlist;
	t_sprite_list	*tmp_prev;
	t_sprite_list	*tmp_prev_prev;
	short			i;

	i = 0;
	mainlist = sec->sprite_list->next;
	tmp_prev = sec->sprite_list;
	while (mainlist)
	{
		if (vla[i] < vla[i + 1])
		{
			tmp_dist = vla[i];
			vla[i] = vla[i + 1];
			vla[i + 1] = tmp_dist;
			if (i == 0)
			{
				tmp_prev->next = mainlist->next;
				mainlist->next = sec->sprite_list;
				sec->sprite_list = mainlist;
				super_unoptimized_reorder_sprite(d, sec, vla);
				return ;
			}
			tmp_prev_prev->next = mainlist;
			tmp_prev->next = mainlist->next;
			mainlist->next = tmp_prev;
			super_unoptimized_reorder_sprite(d, sec, vla);
			return ;
		}
		i++;
		tmp_prev_prev = tmp_prev;
		tmp_prev = mainlist;
		mainlist = mainlist->next;
	}
}

void	set_vla(t_sprite_list *tmp, double *vla, t_data *d)
{
	short	i;

	i = 0;
	while (tmp)
	{
		if (tmp->type == IS_MONSTER)
			vla[i] = vec3f_length(sub_vec3f(d->cam.pos,
						(t_vec3f){d->monsters[tmp->id].pos.x,
						0.0,
						d->monsters[tmp->id].pos.y
						}));
		if (tmp->type == IS_PROJECTILE)
			vla[i] = vec3f_length(sub_vec3f(d->cam.pos,
						d->projectiles[tmp->id].pos));

		i++;
		tmp = tmp->next;
	}
}

void	reorder_sprite(t_data *d, t_sector *sect)
{
	t_sprite_list	*tmp;
	short			i;
	double			*vla;

	i = 0;
	tmp = sect->sprite_list;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (i < 2)
		return ;
	if (!(vla = malloc(sizeof(*vla) * i)))
		exit(EXIT_FAILURE);
	tmp = sect->sprite_list;
	set_vla(tmp, vla, d);
	super_unoptimized_reorder_sprite(d, sect, vla);
	free(vla);
}
