/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m16_recur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:13:02 by nallani           #+#    #+#             */
/*   Updated: 2019/06/29 15:34:54 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_m16_inf		m16_inside_sector(t_data *d, uint16_t sect_to_scan, double dist)
{
	t_sprite_list	*tmp;
	t_vec2f			pos;
	t_m16_inf		inf;

	tmp = d->sectors[sect_to_scan].sprite_list;
	inf.id_of_monst = -1;
	inf.dist = dist;
	while (tmp)
	{
		if (tmp->type == IS_MONSTER && set_pos_m16_inside_sec(d, tmp->id, &pos))
			if (pos.y > 0 && pos.x > -M16_HITBOX -
				d->monster_type[d->monsters[tmp->id].id_type].hitbox_radius &&
				pos.x < M16_HITBOX + d->monster_type[d->
				monsters[tmp->id].id_type].hitbox_radius)
				if (d->monsters[tmp->id].can_collide && (dist == -1 ||
							get_vec2f_length(sub_vec2f(vec3to2(d->cam.pos),
							d->monsters[tmp->id].pos)) < dist))
				{
					inf.id_of_monst = tmp->id;
					inf.dist = vec2f_length(sub_vec2f(vec3to2(d->cam.pos),
								d->monsters[tmp->id].pos));
				}
		tmp = tmp->next;
	}
	return (inf);
}

static double	set_var_m16_recur(t_data *d, short *i, short *j,
		int16_t sect_to_scan)
{
	*i = d->sectors[sect_to_scan].firstwallnum;
	*j = d->sectors[sect_to_scan].firstwallnum +
		d->sectors[sect_to_scan].numwalls - 1;
	return (find_closest_wall_dist(d, sect_to_scan));
}

static	bool	check_dists(double dist, t_data *d, short i, short j)
{
	double	tmp_dist;

	if (dist == -1)
		return (true);
	tmp_dist = get_dist_to_intersect_wall(d, d->walls[j].point,
			d->walls[i].point);
	if (tmp_dist < dist)
		return (true);
	return (false);
}

static bool		check_condition_inside_wall(t_data *d, short i, short j)
{
	t_vec2f tmp;
	t_vec2f	tmp2;

	tmp2 = (t_vec2f){d->cam.pos.x + 1000 * d->cam.sin,
		d->cam.pos.z + 1000 * d->cam.cos};
	tmp = intersect(vec3to2(d->cam.pos), tmp2,
			d->walls[j].point, d->walls[i].point);
	if (is_inside_vec2f(d->walls[j].point, d->walls[i].point, tmp) &&
			is_inside_vec2f(vec3to2(d->cam.pos), tmp2, tmp))
		return (true);
	return (false);
}

t_m16_inf		m16_recur(t_data *d, int16_t sect_to_scan,
		int16_t old_sect)
{
	short		i;
	short		j;
	double		dist;
	t_m16_inf	inf;

	dist = set_var_m16_recur(d, &i, &j, sect_to_scan);
	if ((inf = m16_inside_sector(d, sect_to_scan, dist)).id_of_monst != -1)
		return (inf);
	while (i < d->sectors[sect_to_scan].firstwallnum +
			d->sectors[sect_to_scan].numwalls)
	{
		if (d->walls[j].neighborsect != -1 && d->walls[j].neighborsect !=
				old_sect && d->doorstate[j] > 0.7)
			if (check_dists(dist, d, i, j) &&
					check_condition_inside_wall(d, i, j))
			{
				return (m16_recur(d, d->walls[j].neighborsect,
							sect_to_scan));
			}
		j = i++;
	}
	return (inf);
}
