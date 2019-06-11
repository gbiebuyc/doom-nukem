/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:05:19 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/10 00:04:57 by nallani          ###   ########.fr       */
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
	//	t_vec3f dist = sub_vec3f(vec2to3(monsters[i].pos), d->cam.pos);
	while (i < *nummonsters)
	{
		if (monsters[i].can_collide)
			monster_behaviour(d, &monsters[i]);
		monster_anim_state(&monsters[i], d->monster_type, d);
	//			monsters[i].pos.x -= 0.001 * dist.x;
	//			monsters[i].pos.y -= 0.001 * dist.z;
		;/*appply behavior of monster (return -1 if death)
		   if (behaviour(monsters[i]) == -1) // if monster moved apply inside to change sector
		   {
		  *nummonsters--;
		  *monsters[i] = *monsters[nummonsters];
		  continue;
		  }
		  */	i++;
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
# define NB_OF_SECTOR_DEPTH 2

void	update_projectiles(t_data *d) // NEED TO BE REWORKED
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
				update_anim_projectile(&d->projectiles[i], d, i, false); // in monster_anim_state.c
				i++ ;
				continue ;
			}
			if (d->projectile_type[d->projectiles[i].id_type].threat_to_monster)
				coll = collision_proj_monster(d, &d->sectors[d->projectiles[i].cursectnum], &d->projectiles[i]); //projectile_collision.c
			if (d->projectile_type[d->projectiles[i].id_type].threat_to_player)
				coll = collision_proj_player(d, &d->projectiles[i]); 
			if (!coll && (update_sect =  update_cursect_proj(d->projectiles[i].cursectnum, d,
							NB_OF_SECTOR_DEPTH, -1, d->projectiles[i].pos)) >= 0)
			{
				if (update_sect != d->projectiles[i].cursectnum)
				{
					swap_list(IS_PROJECTILE, i, d, d->projectiles[i].cursectnum,
						update_sect);
					;//update liste chainee
				}
				d->projectiles[i].cursectnum = update_sect;
				update_anim_projectile(&d->projectiles[i], d, i, coll); // in monster_anim_state.c
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

void	update(t_data *d)
{
	int16_t	sect;

	update_doors(d);
	d->cam.rot -= d->keys[SDL_SCANCODE_LEFT] * TURN_SPEED;
	d->cam.rot += d->keys[SDL_SCANCODE_RIGHT] * TURN_SPEED;
	d->cam.sin = sin(d->cam.rot);
	d->cam.cos = cos(d->cam.rot);
//	if (d->keys[SDL_SCANCODE_K])
//	{
//		t_vec2f tmp;
//		tmp = sub_vec2f(vec3to2(d->cam.pos), d->monsters[0].pos);
//		d->monsters[0].anim_state = 4;
//		d->monsters[0].anim_time = 10;
//		d->monsters[0].rot = atan2(tmp.y, tmp.x);
//	}
	movement(d);
	// Update current sector
	/*while (sect < d->numsectors && !inside(d, sect, vec3to2(d->cam.pos)))
		sect++;
	if (sect < d->numsectors)
		d->cursectnum = sect;
		printf("%d\n", sect);*/
	if ((sect = update_cursect_player(d->cursectnum, d, 10, -1)) != -1)
	{
		if (sect != d->cursectnum && d->cam.pos.y < d->sectors[sect].floorheight + d->player.minimum_height)
			d->player.minimum_height = d->cam.pos.y - d->sectors[sect].floorheight;
		d->cursectnum = sect;
	}
	jump(d);
	player_actions(d);
	update_projectiles(d);
	update_monsters(&d->nummonsters, d->monsters, d);
	d->lightblink = sin((double)SDL_GetTicks() / 200) * 0.3 + 0.6;
	d->floor_sin = sin(-d->cam.rot + M_PI_2);
	d->floor_cos = cos(-d->cam.rot + M_PI_2);
}
