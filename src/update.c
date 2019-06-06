/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:05:19 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/30 19:05:02 by gbiebuyc         ###   ########.fr       */
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
		if (!monsters[i].activated)
		{
			i++;
			continue ;
		}
		if (monsters[i].behaviour == 0)	
			monster_behaviour(d, &monsters[i]);
		monster_anim_state(&monsters[i], d->monster_type);
		//		monsters[i].pos.x -= 0.001 * dist.x;
		//		monsters[i].pos.y -= 0.001 * dist.z;
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

void	update(t_data *d)
{
	int16_t	sect;

	update_doors(d);
	d->cam.rot -= d->keys[SDL_SCANCODE_LEFT] * TURN_SPEED;
	d->cam.rot += d->keys[SDL_SCANCODE_RIGHT] * TURN_SPEED;
	d->cam.sin = sin(d->cam.rot);
	d->cam.cos = cos(d->cam.rot);
	d->keys[SDL_SCANCODE_J] ? jump(d, 1) : jump(d, 0); // short jump | long jump
	movement(d);
	// Update current sector
	sect = 0;
	while (sect < d->numsectors && !inside(d, sect))
		sect++;
	if (sect < d->numsectors)
		d->cursectnum = sect;
	gravity(d, 0);
	//player action;
	update_monsters(&d->nummonsters, d->monsters, d);
	d->lightblink = sin((double)SDL_GetTicks() / 200) * 0.3 + 0.6;
}
