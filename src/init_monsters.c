/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monsters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 00:50:16 by nallani           #+#    #+#             */
/*   Updated: 2019/06/07 21:38:45 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	add_monster(t_sector *sector, int16_t id_of_monster)
{
	t_sprite_list	*new_monster_list;
	t_sprite_list	*tmp;

	if (!(new_monster_list = malloc(sizeof(*new_monster_list))))
	{
		ft_putendl_fd("malloc has failed\n", 2);
		exit(EXIT_FAILURE);
	}
	new_monster_list->next = NULL;
	new_monster_list->id = id_of_monster;
	new_monster_list->type = IS_MONSTER;
	if (!(tmp = sector->sprite_list))
	{
		sector->sprite_list = new_monster_list;
		return;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new_monster_list;
}	

void	initialize_all_monster(t_data *d, t_monster *monster, int16_t id_of_monster)
{
	monster->life = monster->health_mult * d->monster_type[monster->id_type].health;
	monster->width = monster->size * d->monster_type[monster->id_type].width;
	monster->height = monster->size * d->monster_type[monster->id_type].height;
	monster->anim_state = 0;
	monster->rot = 1.5 * M_PI;
	monster->behaviour = 0;
	monster->anim_time = 25;
	monster->can_collide = true;
	monster->timer = 0;
	add_monster(&d->sectors[monster->cursectnum], id_of_monster); 
}

void	init_monster_type(t_data *d)
{
	d->monster_type[MOTHERDEMON].width = 0.8;
	d->monster_type[MOTHERDEMON].height = 2.0;
	d->monster_type[MOTHERDEMON].floating = 0.1;
	d->monster_type[MOTHERDEMON].size = 7.0;
	d->monster_type[MOTHERDEMON].health = 1000;
	d->monster_type[MOTHERDEMON].hitbox_radius = 0.7;
	d->monster_type[MOTHERDEMON].id_sprite = MOTHERDEMON;
	d->monster_type[MOTHERDEMON].anim_order[0] = 1;
	d->monster_type[MOTHERDEMON].anim_order[1] = 2;
	d->monster_type[MOTHERDEMON].anim_order[2] = 3;
	d->monster_type[MOTHERDEMON].anim_order[3] = 0;
	d->monster_type[MOTHERDEMON].anim_order[4] = 5;
	d->monster_type[MOTHERDEMON].anim_order[5] = 6;
	d->monster_type[MOTHERDEMON].anim_order[6] = 0;
	d->monster_type[MOTHERDEMON].anim_order[10] = 11;
	d->monster_type[MOTHERDEMON].anim_order[11] = 12;
	d->monster_type[MOTHERDEMON].anim_order[12] = 13;
	d->monster_type[MOTHERDEMON].anim_order[13] = 14;
	d->monster_type[MOTHERDEMON].anim_order[14] = 15;
	d->monster_type[MOTHERDEMON].anim_order[15] = 16;
	d->monster_type[MOTHERDEMON].anim_order[16] = 17;
	d->monster_type[MOTHERDEMON].anim_order[17] = 18;
	d->monster_type[MOTHERDEMON].anim_order[18] = 18;
//	d->monster_type[MOTHERDEMON].anim_order = (uint9_t[MAX_STATE]){1, 2, 3, 1}
}

void	init_monsters(t_data *d)
{
	short	i;

	init_monster_type(d);
	i = 0;
	while (i < d->nummonsters)
	{
		initialize_all_monster(d, &(d->monsters[i]), i);
		i++;
	}
}
