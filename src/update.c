/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:05:19 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/07 08:02:23 by nallani          ###   ########.fr       */
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

void	update(t_data *d)
{
	d->cam.rot -= d->keys[SDL_SCANCODE_LEFT] * TURN_SPEED;
	d->cam.rot += d->keys[SDL_SCANCODE_RIGHT] * TURN_SPEED;
	if (d->cam.rot < 0)// a supp
		d->cam.rot += 2 * M_PI; // mais ptet garder car besoin de %M_PI pour anim sinon
	if (d->cam.rot > 2 * M_PI) // ''
		d->cam.rot -= 2 * M_PI; // ''
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
