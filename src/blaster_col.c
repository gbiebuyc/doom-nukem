/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blaster_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 17:50:43 by nallani           #+#    #+#             */
/*   Updated: 2019/06/07 22:31:45 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

# define BLASTER_HITBOX 0.4
# define LEFT_MOUSE_BLASTER_DAMAGE 1000
# define RIGHT_MOUSE_BLASTER_DAMAGE 750

bool		scan_sect_point_line(t_data *d, uint16_t sect_to_scan, double dist, bool hit_all)
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
			if (pos.y > d->cam.pos.z && pos.x > -BLASTER_HITBOX -
					d->monster_type[d->monsters[tmp->id].id_type].hitbox_radius &&
					pos.x < BLASTER_HITBOX + d->monster_type[d->monsters[tmp->id].id_type].hitbox_radius)
			{
				if (dist == -1 || get_vec2f_length(sub_vec2f(vec3to2(d->cam.pos), d->monsters[tmp->id].pos)) < dist)
				{
					if (hit_all)
						monster_hit(d, RIGHT_MOUSE_BLASTER_DAMAGE, tmp->id);
					if (!hit_all)
					one = tmp->id;
				}
			}
		}
		tmp = tmp->next;
	}
	if (one != -1)
	{
		monster_hit(d, LEFT_MOUSE_BLASTER_DAMAGE, one);
		return (true);
	}
	return (false);
}

double	get_dist_to_intersect_wall(t_data *d, t_vec2f wall1, t_vec2f wall2)
{
	double	dist;
	t_vec2f	intersec;
	t_vec2f	pos2;

	pos2 = (t_vec2f){d->cam.pos.x + 100000 * d->cam.sin,
		d->cam.pos.z + 100000 * d->cam.cos};
	dist = -1;
	intersec = intersect(vec3to2(d->cam.pos), pos2, wall1, wall2);
	if (is_inside_vec2f(wall1, wall2, intersec) && is_inside_vec2f(vec3to2(d->cam.pos), pos2, intersec))
		dist = get_vec2f_length(sub_vec2f(vec3to2(d->cam.pos), intersec));
	return (dist);
}

double	find_closest_wall_dist(t_data *d, uint16_t sect_to_scan)
{
	short	i;
	short	j;
	double	dist;
	t_vec2f	pos2;
	t_vec2f	intersec;

	dist = -1;
	pos2 = (t_vec2f){d->cam.pos.x + 100000 * d->cam.sin,
		d->cam.pos.z + 100000 * d->cam.cos};
	i = d->sectors[sect_to_scan].firstwallnum;
	j = d->sectors[sect_to_scan].firstwallnum + d->sectors[sect_to_scan].numwalls - 1;
	while (i < d->sectors[sect_to_scan].firstwallnum + d->sectors[sect_to_scan].numwalls)
	{
		if (d->walls[j].neighborsect == -1)
		{
			intersec = intersect(vec3to2(d->cam.pos), pos2, d->walls[j].point, d->walls[i].point);
			if (intersec.x == -1 && intersec.y == -1)
				return (dist);
			if (is_inside_vec2f(d->walls[j].point, d->walls[i].point, intersec) && is_inside_vec2f(vec3to2(d->cam.pos), pos2, intersec))
			{
				if (dist == -1 || get_vec2f_length(sub_vec2f(vec3to2(d->cam.pos), intersec)) < dist)
					dist = get_vec2f_length(sub_vec2f(vec3to2(d->cam.pos), intersec));
			}
		}
		j = i;
		i++;
	}
	return (dist);
}

double	recur_scan_point_line(t_data *d, uint8_t depth, uint16_t sect_to_scan,
		uint16_t old_sect, bool hit_all)
{
	short	i;
	short	j;
	double	dist[2];
	bool	has_hit;

	dist[0] = find_closest_wall_dist(d, sect_to_scan);
	i = d->sectors[sect_to_scan].firstwallnum;
	j = d->sectors[sect_to_scan].firstwallnum + d->sectors[sect_to_scan].numwalls - 1;
	if (depth)
		while (i < d->sectors[sect_to_scan].firstwallnum + d->sectors[sect_to_scan].numwalls)
		{
			//printf("cur_sect :%d curwalls :%d, %d, going to sect:%d\n", sect_to_scan, j, i, d->walls[j].neighborsect);
			if (d->walls[j].neighborsect != -1 && d->walls[j].neighborsect != old_sect && d->doorstate[j] > 0.7)
			{
				dist[1] = get_dist_to_intersect_wall(d, d->walls[j].point, d->walls[i].point);
				if (dist[0] == -1 || dist[1] < dist[0])
					if (is_inside_vec2f(d->walls[j].point, d->walls[i].point, intersect(vec3to2(d->cam.pos),
					(t_vec2f){d->cam.pos.x + 1000 * d->cam.sin, d->cam.pos.z + 1000 * d->cam.cos}, d->walls[j].point, d->walls[i].point)))
					{
						dist[0] = recur_scan_point_line(d, depth -1, d->walls[j].neighborsect, sect_to_scan, hit_all);
						break ;
					}
			}
			j = i;
			i++;
		}
	has_hit = scan_sect_point_line(d, sect_to_scan, dist[0], hit_all);
	if (!hit_all && has_hit)
		return (0.1);
	return (dist[0]);
}

void		blaster_shot(t_data *d)
{
	if (d->player.click == RIGHT_CLICK)
	{
	recur_scan_point_line(d, 30, d->cursectnum, -1, true);
	//remove ammo
	}
	if (d->player.click == LEFT_CLICK)
	{
	recur_scan_point_line(d, 30, d->cursectnum, -1, false);
		//remove ammo
	}
}
