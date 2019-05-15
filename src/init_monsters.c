/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monsters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 00:50:16 by nallani           #+#    #+#             */
/*   Updated: 2019/05/07 23:15:37 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	initialize_monster(t_data *d, t_monster *monster)
{
	monster->life = monster->health_mult * d->monster_type[monster->id_type].health;
	monster->width = monster->size * d->monster_type[monster->id_type].width;
	monster->height = monster->size * d->monster_type[monster->id_type].height;
	monster->anim_state = 0;
	monster->rot = 1.5 * M_PI;
	monster->behaviour = 0;
	monster->anim_time = 25;;
	monster->activated = true;
}

void	init_monster_list(t_data *d)
{
	d->monster_type[0].width = 0.8;
	d->monster_type[0].height = 2.0;
	d->monster_type[0].floating = 0.1;
	d->monster_type[0].health = 1000;
	d->monster_type[0].id_sprite = 0;
	d->monster_type[0].anim_order[0] = 1;
	d->monster_type[0].anim_order[1] = 2;
	d->monster_type[0].anim_order[2] = 3;
	d->monster_type[0].anim_order[3] = 0;
//	d->monster_type[0].anim_order = (uint8_t[MAX_STATE]){1, 2, 3, 1}
}

void	init_monsters(t_data *d)
{
	short	i;

	init_monster_list(d);
	i = 0;
	while (i < d->nummonsters)
	{
		initialize_monster(d, &(d->monsters[i]));
		i++;
	}
}