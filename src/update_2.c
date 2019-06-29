/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 16:32:28 by nallani           #+#    #+#             */
/*   Updated: 2019/06/29 16:41:09 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define NB_OF_SECTOR_DEPTH 2

void	update_monsters(uint16_t *nummonsters,
		t_monster monsters[MAXNUMMONSTERS], t_data *d)
{
	short	i;

	i = 0;
	(void)d;
	(void)monsters;
	while (i < *nummonsters)
	{
		if (monsters[i].can_collide)
			monster_behaviour(d, &monsters[i], i);
		monster_anim_state(&monsters[i], d->monster_type, d);
		i++;
	}
}

void	update_projectile_2(t_data *d, short i, bool coll)
{
	int16_t	update_sect;

	update_sect = 0;
	if (!coll && (update_sect = update_cursect_proj((int16_t[2]){
					d->projectiles[i].cursectnum, -1}, d, NB_OF_SECTOR_DEPTH,
					d->projectiles[i].pos)) >= 0)
	{
		if (update_sect != d->projectiles[i].cursectnum)
		{
			swap_list(IS_PROJECTILE, i, d,
					(int[2]){d->projectiles[i].cursectnum, update_sect});
		}
		d->projectiles[i].cursectnum = update_sect;
		update_anim_projectile(&d->projectiles[i], d, i, coll);
	}
	else if (update_sect == -2)
	{
		d->projectiles[i].is_active = false;
		destroy_mail(i, &d->sectors[d->projectiles[i].cursectnum],
				IS_PROJECTILE);
	}
	else
		update_anim_projectile(&d->projectiles[i], d, i, true);
}

void	update_projectiles(t_data *d)
{
	short	i;
	bool	coll;

	i = 0;
	coll = false;
	while (i < MAX_PROJECTILES)
	{
		if (d->projectiles[i].is_active)
		{
			if (d->projectiles[i].has_collided)
			{
				update_anim_projectile(&d->projectiles[i], d, i, false);
				i++;
				continue ;
			}
			if (d->projectile_type[d->projectiles[i].id_type].threat_to_monster)
				coll = collision_proj_monster(d, &d->sectors[d->projectiles[i].
						cursectnum], &d->projectiles[i]);
			if (d->projectile_type[d->projectiles[i].id_type].threat_to_player)
				coll = collision_proj_player(d, &d->projectiles[i]);
			update_projectile_2(d, i, coll);
		}
		i++;
	}
}

void	update_2(t_data *d)
{
	jump(d);
	player_actions(d);
	update_monsters(&d->nummonsters, d->monsters, d);
	update_projectiles(d);
	d->lightblink = sin((double)SDL_GetTicks() / 200) * 0.3 + 0.6;
	check_dangerous_area(d);
}
