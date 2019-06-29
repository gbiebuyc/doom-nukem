/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_behaviour_chargingdemon.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kits <unkown@noaddress.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 18:58:56 by Kits              #+#    #+#             */
/*   Updated: 2019/06/29 14:58:08 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define COLLISION_RANGE_CHARGINGDEMON 0.2

static void	behaviour_update_charge(t_data *d, t_monster *monster)
{
	t_vec2f	tmp;
	double	new_angle;

	tmp = sub_vec2f(monster->pos, vec3to2(d->cam.pos));
	new_angle = atan2(tmp.y, tmp.x) + M_PI;
	monster->dir = mul_vec2f(monster->dir, 0.9);
	tmp.x = 0.015;
	tmp.y = 0.0;
	actualize_dir(new_angle, &tmp);
	monster->dir = add_vec2f(monster->dir, tmp);
	monster->rot = atan2(monster->dir.y, monster->dir.x);
	monster->pos = add_vec2f(monster->pos, monster->dir);
}

void		charging_demon_wait(t_data *d, t_monster *monster)
{
	monster->dir = (t_vec2f){0.0, 0.0};
	monster->timer = 30;
	if (monster->anim_state < 4)
	{
		monster->anim_state = 4;
		monster->anim_time = 17;
	}
}

static void	update_cursect_chargingdemon(t_data *d, t_monster *monster,
		uint16_t id)
{
	int16_t		new_sect;

	new_sect = update_cursect_smart(d, 2, monster->pos, monster->cursectnum);
	if (new_sect != monster->cursectnum && new_sect != -1)
	{
		swap_list(IS_MONSTER, id, d, (int[2]){monster->cursectnum, new_sect});
		monster->cursectnum = new_sect;
	}
}

void		monster_behaviour_chargingdemon(t_data *d, t_monster *monster,
		uint16_t id)
{
	t_vec2f		tmp;

	if (monster->timer == 0 && monster->dir.x == 0.0)
	{
		tmp = sub_vec2f(monster->pos, vec3to2(d->cam.pos));
		monster->rot = atan2(tmp.y, tmp.x) + M_PI;
		tmp.x = 0.02;
		tmp.y = 0.0;
		actualize_dir(monster->rot, &tmp);
		monster->dir = tmp;
		monster->timer = 0xFF;
		monster->anim_state = 0;
		monster->anim_time = 7;
	}
	if (monster->timer && monster->dir.x != 0)
		behaviour_update_charge(d, monster);
	collision_monster_monster(d, monster->cursectnum, monster);
	while (collision_monster_wall(d, &d->sectors[monster->cursectnum],
				&monster->pos, COLLISION_RANGE_CHARGINGDEMON))
		if (monster->timer < 240)
			charging_demon_wait(d, monster);
	update_cursect_chargingdemon(d, monster, id);
}
