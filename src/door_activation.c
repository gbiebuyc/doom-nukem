/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_activation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 13:25:48 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/27 13:26:05 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	activate_neighbor_door(t_data *d, t_wall *door,
		t_wall *nextwall, t_sector *nei)
{
	int16_t lastwall = nei->firstwallnum + nei->numwalls - 1;
	for (int i = lastwall, j = nei->firstwallnum; j < lastwall; i = j++)
	{
		if (d->walls[i].neighborsect == -1)
			continue ;
		t_vec2f a = d->walls[i].point;
		t_vec2f b = d->walls[j].point;
		if (a.x == nextwall->point.x && a.y == nextwall->point.y &&
				b.x == door->point.x && b.y == door->point.y)
		{
			d->doorstate[i] = d->doorstate[door - d->walls];
			d->dooranimstep[i] = d->dooranimstep[door - d->walls];
			return;
		}
	}
}

#define ACTIVATION_DIST 2

void	activate_door(t_data *d)
{
	t_sector *sect = d->sectors + d->cursectnum;
	int16_t lastwall = sect->firstwallnum + sect->numwalls - 1;
	t_vec2f p = (t_vec2f){d->cam.pos.x, d->cam.pos.z};
	for (int i = lastwall, j = sect->firstwallnum; j < lastwall; i = j++)
	{
		if (d->walls[i].neighborsect == -1)
			continue ;
		t_vec2f a = d->walls[i].point;
		t_vec2f b = d->walls[j].point;
		t_vec2f a_to_p = {p.x - a.x, p.y - a.y};
		t_vec2f	a_to_b = {b.x - a.x, b.y - a.y};
		double	atb2 = a_to_b.x * a_to_b.x + a_to_b.y * a_to_b.y;
		double	atp_dot_atb = a_to_p.x * a_to_b.x + a_to_p.y * a_to_b.y;
		double	t = atp_dot_atb / atb2;
		t = fclamp(t, 0, 1);
		t_vec2f	closest = {a.x + t * a_to_b.x, a.y + t * a_to_b.y};
		double	dx = p.x - closest.x;
		double	dy = p.y - closest.y;
		double	dist = vec2f_length((t_vec2f){dx, dy});
		if (dist > ACTIVATION_DIST)
			continue ;
		if (d->doorstate[i] == 0 || d->dooranimstep[i] < 0)
			d->dooranimstep[i] = 0.01;
		else if (d->doorstate[i] == 1 || d->dooranimstep[i] > 0)
			d->dooranimstep[i] = -0.01;
		activate_neighbor_door(d, &d->walls[i], &d->walls[j],
				&d->sectors[d->walls[i].neighborsect]);
		return;
	}
}
