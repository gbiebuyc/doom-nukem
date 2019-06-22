/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 21:50:12 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/21 21:50:12 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

# define COLLISION_DIST 0.3
# define MINIMUM_HEIGHT_TO_WALK 0.32
# define MINIMUM_CEIL_DIST 0.1

bool	can_traverse(t_data *d, int i, t_wall *wall)
{
	int16_t neighbor;

	neighbor = wall->neighborsect;
	return (wall->neighborsect != -1 &&
			wall->is_transparent == false &&
			d->doorstate[i] > 0.7 &&
			d->cam.pos.y + d->player.minimum_height > get_floorheight_player(d,
				neighbor) + MINIMUM_HEIGHT_TO_WALK &&
			(d->sectors[neighbor].outdoor ||
			 (d->cam.pos.y < get_ceilheight_player(d, neighbor) &&
			  get_ceilheight_player(d, neighbor) - get_floorheight_player(d,
				  neighbor) - MINIMUM_CEIL_DIST > d->player.minimum_height)));
}

bool	collision(t_data *d, t_sector *sect)
{
	static int	recursion;
	if (recursion >= 3)
		return (false);
	recursion++;
	int16_t last = sect->firstwallnum + sect->numwalls;
	bool collided = false;
	for (int i = last - 1, j = sect->firstwallnum; j < last; i = j++)
	{
		t_vec2f a = d->walls[i].point;
		t_vec2f b = d->walls[j].point;
		t_vec2f p = (t_vec2f){d->cam.pos.x, d->cam.pos.z};
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
		if (dist > COLLISION_DIST)
			continue ;
		if (can_traverse(d, i, &d->walls[i]))
			collided |= collision(d, &d->sectors[d->walls[i].neighborsect]);
		else
		{
			d->cam.pos.x = closest.x + dx * COLLISION_DIST * 1.001 / dist;
			d->cam.pos.z = closest.y + dy * COLLISION_DIST * 1.002 / dist;
			collided = true;
		}
	}
	recursion--;
	return (collided);
}
