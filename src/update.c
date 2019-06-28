/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:05:19 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/28 15:38:46 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define TURN_SPEED 0.02

void	update_monsters(uint16_t *nummonsters, t_monster monsters[MAXNUMMONSTERS], t_data *d)
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

void	update_doors(t_data *d)
{
	int i;

	i = -1;
	while (++i < MAXNUMWALLS)
	{
		if (!d->walls[i].is_door || d->walls[i].neighborsect == -1)
			d->doorstate[i] = 1;
		else
		{
			d->doorstate[i] += d->dooranimstep[i];
			if (d->doorstate[i] >= 1 || d->doorstate[i] <= 0)
			{
				d->doorstate[i] = fclamp(d->doorstate[i], 0, 1);
				d->dooranimstep[i] = 0;
			}
		}
	}
}

#define NB_OF_SECTOR_DEPTH 2

void	update_projectiles(t_data *d)
{
	short	i;
	bool	coll;
	int16_t	update_sect;

	i = 0;
	coll = false;
	update_sect = 0;
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
				coll = collision_proj_monster(d, &d->sectors[d->projectiles[i].cursectnum], &d->projectiles[i]);
			if (d->projectile_type[d->projectiles[i].id_type].threat_to_player)
				coll = collision_proj_player(d, &d->projectiles[i]);
			if (!coll && (update_sect = update_cursect_proj(d->projectiles[i].cursectnum, d,
							NB_OF_SECTOR_DEPTH, -1, d->projectiles[i].pos)) >= 0)
			{
				if (update_sect != d->projectiles[i].cursectnum)
				{
					swap_list(IS_PROJECTILE, i, d, (int[2]){d->projectiles[i].cursectnum,
						update_sect});
				}
				d->projectiles[i].cursectnum = update_sect;
				update_anim_projectile(&d->projectiles[i], d, i, coll);
			}
			else if (update_sect == -2)
			{
				d->projectiles[i].is_active = false;
				destroy_mail(i, &d->sectors[d->projectiles[i].cursectnum], IS_PROJECTILE);
			}
			else
			{
				update_anim_projectile(&d->projectiles[i], d, i, true);
			}
		}
		i++;
	}
}

#define DEPTH_TO_SCAN 10

void	update(t_data *d)
{
	int16_t	sect;

	if (d->player.health <= 0)
		handle_respawn(d);
	if (d->sectors[d->cursectnum].is_finish)
		handle_finish(d);
	update_doors(d);
	d->cam.rot -= d->keys[SDL_SCANCODE_LEFT] * TURN_SPEED;
	d->cam.rot += d->keys[SDL_SCANCODE_RIGHT] * TURN_SPEED;
	d->cam.sin = sin(d->cam.rot);
	d->cam.cos = cos(d->cam.rot);
	movement(d);
	asset_collision(d);
	if ((sect = update_cursect_smart(d, DEPTH_TO_SCAN, vec3to2(d->cam.pos),
	d->cursectnum)) != -1)
	{
		if (sect != d->cursectnum && d->cam.pos.y < get_floorheight_player(d, sect) + d->player.minimum_height)
			d->player.minimum_height = d->cam.pos.y - get_floorheight_player(d, sect);
		d->cursectnum = sect;
	}
	jump(d);
	player_actions(d);
	update_monsters(&d->nummonsters, d->monsters, d);
	update_projectiles(d);
	d->lightblink = sin((double)SDL_GetTicks() / 200) * 0.3 + 0.6;
	check_dangerous_area(d);
}
