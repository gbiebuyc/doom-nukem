/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_activation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 13:25:48 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/27 16:38:01 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	activate_neighbor_door(t_data *d, t_wall *door,
		t_wall *nextwall, t_sector *nei)
{
	int16_t last;
	int		i;
	int		j;
	t_vec2f a;
	t_vec2f b;

	last = nei->firstwallnum + nei->numwalls;
	i = last - 1;
	j = nei->firstwallnum;
	while (j < last)
	{
		if (d->walls[i].neighborsect >= 0)
		{
			a = d->walls[i].point;
			b = d->walls[j].point;
			if (a.x == nextwall->point.x && a.y == nextwall->point.y &&
					b.x == door->point.x && b.y == door->point.y)
			{
				d->doorstate[i] = d->doorstate[door - d->walls];
				d->dooranimstep[i] = d->dooranimstep[door - d->walls];
				return ;
			}
		}
		i = j++;
	}
}

double	get_dist(t_vec2f a, t_vec2f b, t_vec2f p)
{
	t_vec2f v[3];
	double	n[5];

	v[0] = (t_vec2f){p.x - a.x, p.y - a.y};
	v[1] = (t_vec2f){b.x - a.x, b.y - a.y};
	n[0] = v[1].x * v[1].x + v[1].y * v[1].y;
	n[1] = v[0].x * v[1].x + v[0].y * v[1].y;
	n[2] = n[1] / n[0];
	n[2] = fclamp(n[2], 0, 1);
	v[2] = (t_vec2f){a.x + n[2] * v[1].x, a.y + n[2] * v[1].y};
	n[3] = p.x - v[2].x;
	n[4] = p.y - v[2].y;
	return (vec2f_length((t_vec2f){n[3], n[4]}));
}

#define ACTIVATION_DIST 1.5

bool	activate_door(t_data *d, t_sector *sect)
{
	int		n[4];
	double	m[2];

	n[0] = 0;
	n[1] = 0;
	m[1] = INFINITY;
	n[2] = sect->firstwallnum + sect->numwalls - 1;
	n[3] = sect->firstwallnum;
	while (n[3] < sect->firstwallnum + sect->numwalls)
	{
		if (d->walls[n[2]].is_door && d->walls[n[2]].neighborsect >= 0 &&
				(m[0] = get_dist(d->walls[n[2]].point, d->walls[n[3]].point,
				vec3to2(d->cam.pos))) < ACTIVATION_DIST && m[0] < m[1] &&
					(m[1] = m[0]) >= 0 &&
					(n[0] = n[2]) >= 0)
			n[1] = n[3];
		n[2] = n[3]++;
	}
	if (m[1] == INFINITY)
		return (false);
	d->dooranimstep[n[0]] = (d->doorstate[n[0]] == 0 ||
			d->dooranimstep[n[0]] < 0) ? 0.01 : -0.01;
	activate_neighbor_door(d, &d->walls[n[0]], &d->walls[n[1]],
			&d->sectors[d->walls[n[0]].neighborsect]);
	return (true);
}

bool	pickup_asset(t_data *d)
{
	int			i;
	t_assets	*asset;

	i = -1;
	while (d->nb_assets && ++i < d->assets[d->cursectnum][0].nb_assets)
	{
		asset = &d->assets[d->cursectnum][i];
		if (vec2f_length(sub_vec2f(vec3to2(d->cam.pos), asset->world_pos)) <
				ACTIVATION_DIST && !asset->used &&
				(asset->is_interactive || asset->is_autopick))
		{
			use_asset(d, asset);
			return (true);
		}
	}
	return (false);
}

void	activate_or_pickup(t_data *d)
{
	if (pickup_asset(d))
		return ;
	else if (activate_door(d, &d->sectors[d->cursectnum]))
		return ;
}
