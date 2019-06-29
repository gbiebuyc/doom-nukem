/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorder_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 00:15:00 by nallani           #+#    #+#             */
/*   Updated: 2019/06/29 16:11:02 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define INCREMENT true
#define SET false

static void	set_var_reorder_sprite(t_sprite_list **list, t_sector *sec, int *i,
		bool type)
{
	if (type == SET)
	{
		list[2] = sec->sprite_list->next;
		list[1] = sec->sprite_list;
		*i = 0;
	}
	if (type == INCREMENT)
	{
		*i = *i + 1;
		list[0] = list[1];
		list[1] = list[2];
		list[2] = list[2]->next;
	}
}

void		change_list(t_sprite_list *one, t_sprite_list *two,
		t_sprite_list *prev)
{
	prev->next = two;
	one->next = two->next;
	two->next = one;
}

void		reorder_sprites_algo(t_data *d, t_sector *sec, double *vla,
		t_sprite_list **list)
{
	double		tmp_dist;
	int			i;

	set_var_reorder_sprite(list, sec, &i, SET);
	while (list[2])
	{
		if (vla[i] < vla[i + 1])
		{
			tmp_dist = vla[i];
			vla[i] = vla[i + 1];
			vla[i + 1] = tmp_dist;
			if (i == 0)
			{
				list[1]->next = list[2]->next;
				list[2]->next = sec->sprite_list;
				sec->sprite_list = list[2];
				reorder_sprites_algo(d, sec, vla, list);
				return ;
			}
			change_list(list[1], list[2], list[0]);
			reorder_sprites_algo(d, sec, vla, list);
			return ;
		}
		set_var_reorder_sprite(list, sec, &i, INCREMENT);
	}
}

void		set_vla(t_sprite_list *tmp, double *vla, t_data *d)
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

void		reorder_sprite(t_data *d, t_sector *sect)
{
	t_sprite_list	*tmp;
	short			i;
	double			*vla;
	t_sprite_list	*list[3];

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
	reorder_sprites_algo(d, sect, vla, &list[0]);
	free(vla);
}
