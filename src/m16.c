/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m16.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 23:32:39 by nallani           #+#    #+#             */
/*   Updated: 2019/06/07 23:43:54 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

# define M16_DAMAGE 80
# define M16_HITBOX 0.4

double	m16_inside_sector(t_data *d, uint16_t sect_to_scan, double dist)
{
	t_sprite_list	*tmp;
	t_vec2f			pos;
	int16_t			one;

	tmp = d->sectors[sect_to_scan].sprite_list;
	one = -1;
	while (tmp)
	{
		if (tmp->type == IS_MONSTER)
		{
			pos = d->monsters[tmp->id].pos;
			pos.x -= d->cam.pos.x;
			pos.y -= d->cam.pos.z;
			actualize_dir(d->cam.rot, &pos);
			if (pos.y > d->cam.pos.z && pos.x > -M16_HITBOX -
					d->monster_type[d->monsters[tmp->id].id_type].hitbox_radius &&
					pos.x < M16_HITBOX + d->monster_type[d->monsters[tmp->id].id_type].hitbox_radius)
			{
				if (dist == -1 || get_vec2f_length(sub_vec2f(vec3to2(d->cam.pos), d->monsters[tmp->id].pos)) < dist)
				{
					one = tmp->id;
				}
			}
		}
		tmp = tmp->next;
	}
	if (one != -1)
		monster_hit(d, M16_DAMAGE, one);
	return (dist);
}

double	m16_recur(t_data *d, uint8_t depth, uint16_t sect_to_scan,
		uint16_t old_sect)
{
	short	i;
	short	j;
	double	dist[2];

	dist[0] = find_closest_wall_dist(d, sect_to_scan);
	i = d->sectors[sect_to_scan].firstwallnum;
	j = d->sectors[sect_to_scan].firstwallnum + d->sectors[sect_to_scan].numwalls - 1;
	if (depth)
		while (i < d->sectors[sect_to_scan].firstwallnum + d->sectors[sect_to_scan].numwalls)
		{
			if (d->walls[j].neighborsect != -1 && d->walls[j].neighborsect != old_sect && d->doorstate[j] > 0.7)
			{
				dist[1] = get_dist_to_intersect_wall(d, d->walls[j].point, d->walls[i].point);
				if (dist[0] == -1 || dist[1] < dist[0])
					if (is_inside_vec2f(d->walls[j].point, d->walls[i].point, intersect(vec3to2(d->cam.pos),
					(t_vec2f){d->cam.pos.x + 1000 * d->cam.sin, d->cam.pos.z + 1000 * d->cam.cos}, d->walls[j].point, d->walls[i].point)))
					{
						dist[0] = m16_recur(d, depth -1, d->walls[j].neighborsect, sect_to_scan);
						break ;
					}
			}
			j = i;
			i++;
		}
	dist[0] = m16_inside_sector(d, sect_to_scan, dist[0]);
	return (dist[0]);
}

void	m16_shoot(t_data *d)
{
	double	dist;
	dist = m16_recur(d, 30, d->cursectnum, -1);
}
