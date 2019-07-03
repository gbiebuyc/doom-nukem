/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monsters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 00:50:16 by nallani           #+#    #+#             */
/*   Updated: 2019/07/03 17:35:52 by nallani          ###   ########.fr       */
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
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new_monster_list;
}

void	initialize_all_monster(t_data *d,
		t_monster *monster, int16_t id_of_monster)
{
	monster->life = d->monster_type[monster->id_type].health;
	monster->anim_state = 0;
	monster->rot = 1.5 * M_PI;
	monster->anim_time = 25;
	monster->can_collide = true;
	monster->timer = 0;
	add_monster(&d->sectors[monster->cursectnum], id_of_monster);
}

void	init_monster_type_2(t_data *d)
{
	d->monster_type[CHARGINGDEMON].height = 1.5;
	d->monster_type[CHARGINGDEMON].floating = 0.1;
	d->monster_type[CHARGINGDEMON].size = 6.0;
	d->monster_type[CHARGINGDEMON].health = d->difficulty == HARD ? 110 : 70;
	d->monster_type[CHARGINGDEMON].hitbox_radius = 0.6;
	d->monster_type[CHARGINGDEMON].anim_order[0] = 1;
	d->monster_type[CHARGINGDEMON].anim_order[1] = 2;
	d->monster_type[CHARGINGDEMON].anim_order[2] = 3;
	d->monster_type[CHARGINGDEMON].anim_order[3] = 0;
	d->monster_type[CHARGINGDEMON].anim_order[4] = 5;
	d->monster_type[CHARGINGDEMON].anim_order[5] = 6;
	d->monster_type[CHARGINGDEMON].anim_order[6] = 4;
	d->monster_type[CHARGINGDEMON].anim_order[13] = 14;
	d->monster_type[CHARGINGDEMON].anim_order[14] = 15;
	d->monster_type[CHARGINGDEMON].anim_order[15] = 16;
	d->monster_type[CHARGINGDEMON].anim_order[16] = 17;
	d->monster_type[CHARGINGDEMON].anim_order[17] = 18;
	d->monster_type[CHARGINGDEMON].anim_order[18] = 18;
}

void	init_monster_type(t_data *d)
{
	short	i;

	d->monster_type[MOTHERDEMON].height = 2.0;
	d->monster_type[MOTHERDEMON].floating = 0.1;
	d->monster_type[MOTHERDEMON].size = 7.0;
	d->monster_type[MOTHERDEMON].health = d->difficulty == HARD ? 90 : 50;
	d->monster_type[MOTHERDEMON].hitbox_radius = 0.7;
	d->monster_type[MOTHERDEMON].anim_order[0] = 1;
	d->monster_type[MOTHERDEMON].anim_order[1] = 2;
	d->monster_type[MOTHERDEMON].anim_order[2] = 3;
	d->monster_type[MOTHERDEMON].anim_order[3] = 0;
	d->monster_type[MOTHERDEMON].anim_order[4] = 5;
	d->monster_type[MOTHERDEMON].anim_order[5] = 6;
	d->monster_type[MOTHERDEMON].anim_order[6] = 0;
	i = 10;
	while (i < 18)
	{
		d->monster_type[MOTHERDEMON].anim_order[i] = i + 1;
		i++;
	}
	d->monster_type[MOTHERDEMON].anim_order[18] = 18;
	d->monster_type[MOTHERDEMON].id_of_proj = FIREBALL_1;
}

void	init_monsters(t_data *d)
{
	short	i;

	init_monster_type(d);
	init_monster_type_2(d);
	i = 0;
	while (i < d->nummonsters)
	{
		initialize_all_monster(d, &(d->monsters[i]), i);
		i++;
	}
}
