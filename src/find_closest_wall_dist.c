/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_wall_dist.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 11:47:34 by nallani           #+#    #+#             */
/*   Updated: 2019/06/29 12:05:46 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	set_var_find_closest_wall(t_data *d, t_vec2f *pos2, short *j,
		uint16_t sect_to_scan)
{
	*pos2 = (t_vec2f){d->cam.pos.x + 100000 * d->cam.sin,
		d->cam.pos.z + 100000 * d->cam.cos};
	*j = d->sectors[sect_to_scan].firstwallnum +
		d->sectors[sect_to_scan].numwalls - 1;
}

static void	set_dist_if_intersec(t_data *d, double *dist, t_vec2f intersec)
{
	double		tmp;

	tmp = get_vec2f_length(sub_vec2f(vec3to2(d->cam.pos), intersec));
	if (*dist < tmp || *dist == -1)
		*dist = tmp;
	return ;
}

double		find_closest_wall_dist(t_data *d, uint16_t sect_to_scan)
{
	short	i;
	short	j;
	double	dist;
	t_vec2f	pos2;
	t_vec2f	intersec;

	dist = -1;
	set_var_find_closest_wall(d, &pos2, &j, sect_to_scan);
	i = d->sectors[sect_to_scan].firstwallnum;
	while (i < d->sectors[sect_to_scan].firstwallnum +
			d->sectors[sect_to_scan].numwalls)
	{
		if (d->walls[j].neighborsect == -1 || d->doorstate[j] < 0.7)
		{
			intersec = intersect(vec3to2(d->cam.pos), pos2, d->walls[j].point,
					d->walls[i].point);
			if (intersec.x != -1 && intersec.y != -1 && is_inside_vec2f(
						d->walls[j].point, d->walls[i].point, intersec)
					&& is_inside_vec2f(vec3to2(d->cam.pos), pos2, intersec))
				set_dist_if_intersec(d, &dist, intersec);
		}
		j = i;
		i++;
	}
	return (dist);
}
