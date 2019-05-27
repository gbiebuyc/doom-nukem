/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:04:53 by nallani           #+#    #+#             */
/*   Updated: 2019/05/27 15:16:21 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MOVE_SPEED 0.08
#define COLLISION_DIST 0.3

bool	collision(t_data *d, int16_t sectnum)
{
	static int	recursion;

	if (recursion >= 2)
		return (false);
	recursion++;
	t_sector *sect = d->sectors + sectnum;
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
		int16_t neighbor = d->walls[i].neighborsect;
		if (neighbor != -1 && d->doorstate[i] > 0.5)
			collided |= collision(d, neighbor);
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

void	movement(t_data *d)
{
	if (d->keys[SDL_SCANCODE_W])
	{
		d->cam.pos.z += d->cam.cos * MOVE_SPEED;
		d->cam.pos.x += d->cam.sin * MOVE_SPEED;
	}
	if (d->keys[SDL_SCANCODE_S])
	{
		d->cam.pos.z -= d->cam.cos * MOVE_SPEED;
		d->cam.pos.x -= d->cam.sin * MOVE_SPEED;
	}
	if (d->keys[SDL_SCANCODE_A])
	{
		d->cam.pos.z += d->cam.sin * MOVE_SPEED;
		d->cam.pos.x -= d->cam.cos * MOVE_SPEED;
	}
	if (d->keys[SDL_SCANCODE_D])
	{
		d->cam.pos.z -= d->cam.sin * MOVE_SPEED;
		d->cam.pos.x += d->cam.cos * MOVE_SPEED;
	}
	d->cam.pos.y += d->keys[SDL_SCANCODE_SPACE] * MOVE_SPEED;
	d->cam.pos.y -= d->keys[SDL_SCANCODE_LSHIFT] * MOVE_SPEED;
	while (collision(d, d->cursectnum))
		;
}
