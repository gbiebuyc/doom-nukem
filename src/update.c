/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:05:19 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/07 04:05:43 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define TURN_SPEED 0.02

void	update_monsters(uint16_t *nummonsters, t_monster monsters[MAXNUMMONSTERS], t_data *d)
{
	short	i;

	i = 0;
	(void)monsters;
	t_vec3f dist = sub_vec3f(vec2to3(monsters[i].pos), d->cam.pos);
	while (i < *nummonsters)
	{
		monsters[i].pos.x -= 0.001 * dist.x;
		monsters[i].pos.y -= 0.001 * dist.z;
		;/*appply behavior of monster (return -1 if death)
		if (behaviour(monsters[i]) == -1)
		{
			*nummonsters--;
			*monsters[i] = *monsters[nummonsters];
			continue;
		}
	*/	i++;
	}
}

void	update(t_data *d)
{
	d->cam.rot -= d->keys[SDL_SCANCODE_LEFT] * TURN_SPEED;
	d->cam.rot += d->keys[SDL_SCANCODE_RIGHT] * TURN_SPEED;
	d->cam.sin = sin(d->cam.rot);
	d->cam.cos = cos(d->cam.rot);
	if (d->keys[SDL_SCANCODE_J])
		jump(d);
	movement(d);

	// Update current sector
	t_sector sect = d->sectors[d->cursectnum];
	for (int i = 0; i < sect.numwalls; i++)
	{
		int16_t neighborsect = d->walls[sect.firstwallnum + i].neighborsect;
		if (neighborsect != -1 && inside(d, neighborsect))
		{
			d->cursectnum = neighborsect;
			//printf("You are now inside sector %d\n", neighborsect);
			break ;
		}
	}
	gravity(d, 0);
	//player action;
	update_monsters(&d->nummonsters, d->monsters, d);
}
