/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_behaviour.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 22:40:39 by nallani           #+#    #+#             */
/*   Updated: 2019/06/28 18:09:38 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define ACTIVATION_RADIUS 6
#define LONG_RANGE 7
#define COLLISION_DIST_MOTHERDEMON 1.0

bool	motherdemon_behaviour_change_after_attack(t_data *d,
		t_monster *monster, double rand, t_vec2f tmp)
{
	t_vec2f	tmp2;

	if (vec2f_length(sub_vec2f(vec3to2(d->cam.pos), monster->pos))
			< LONG_RANGE)
	{
		rand = ((abs((int)(monster->pos.x * 1000)) % 63) + 1);
		if (!(SDL_GetTicks() % 6))
			return false;
		rand = rand - (int)(rand / (2 * M_PI)) * 2 * M_PI;
		actualize_dir(rand, &tmp);
		monster->rot = rand;
		monster->dir = tmp;
		monster->timer = 100;
	}
	else
	{
		tmp2 = sub_vec2f(monster->pos, vec3to2(d->cam.pos));
		rand = atan2(tmp2.y, tmp2.x) + M_PI;
		actualize_dir(rand, &tmp);
		monster->dir = tmp;
		monster->rot = rand;
		monster->timer = 100;
	}
	return true;
}

void	motherdemon_behaviour_change_pattern(t_data *d, t_monster *monster)
{
	t_vec2f tmp;
	double	rand;
	bool	ret;

	tmp.x = 0.03;
	tmp.y = 0.0;
	rand = 0;
	ret = false;
	if (monster->anim_state == 6)
		ret = motherdemon_behaviour_change_after_attack(d, monster, rand, tmp);
	if (!ret)
	{
		tmp = sub_vec2f(vec3to2(d->cam.pos), monster->pos);
		monster->anim_state = 4;
		monster->anim_time = 10;
		monster->rot = atan2(tmp.y, tmp.x);
		monster->timer = 29;
	}

}
void	motherdemon_behaviour(t_data *d, t_monster *monster, uint16_t id)
{
	short	new_sect;

	if (monster->timer > 0)
	{
		if (monster->anim_state < 4)
		{
			monster->pos = add_vec2f(monster->pos, monster->dir);
			collision_monster_monster(d, monster->cursectnum, monster);
			while (collision_monster_wall(d, &d->sectors[monster->cursectnum],
						&monster->pos, COLLISION_DIST_MOTHERDEMON))
			{
				if (monster->timer > 2)
					monster->timer -= 2;
			}
			new_sect = update_cursect_smart(d, 2, monster->pos,
					monster->cursectnum);
			if (new_sect != monster->cursectnum && new_sect != -1)
			{
				swap_list(IS_MONSTER, id,  d, (int[2]){monster->cursectnum,
						new_sect});
				monster->cursectnum = new_sect;
			}
		}
		//need other kind of patterns ?
	}
	if (!monster->timer)
		motherdemon_behaviour_change_pattern(d, monster);
}

void	check_activation(t_data *d, t_monster *monster, t_vec2f pos, bool recur)
{
	t_sprite_list	*tmp;

	if (vec2f_length(sub_vec2f(monster->pos, pos)) <
		ACTIVATION_RADIUS)
	{
		monster->activated = true;
		monster->timer = 2;
	}
	if (!recur || monster->activated == false)
		return ;
	tmp = d->sectors[monster->cursectnum].sprite_list;
	while (tmp)
	{
		if (tmp->type == IS_MONSTER && d->monsters[tmp->id].activated == false)
			check_activation(d, &d->monsters[tmp->id], monster->pos, false);
		tmp = tmp->next;
	}
}

void	monster_behaviour(t_data *d, t_monster *monster, uint16_t id)
{
	if (!monster->can_collide) // all monster collide so far, used for monster is dead
		return ;
	if (!monster->activated)
	check_activation(d, monster, vec3to2(d->cam.pos), true);
	if (!monster->activated)
		return ;
	monster->timer--;
	if (monster->id_type == MOTHERDEMON)
		motherdemon_behaviour(d, monster, id);
	if (monster->id_type == CHARGINGDEMON)
		monster_behaviour_chargingdemon(d, monster, id);
}
