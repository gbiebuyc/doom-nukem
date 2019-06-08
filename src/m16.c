/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m16.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 23:32:39 by nallani           #+#    #+#             */
/*   Updated: 2019/06/08 20:26:03 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

# define M16_DAMAGE 80
# define M16_HITBOX 0.4
# define Y_OFFSET_TO_ROT -0.00125

t_m16_inf	m16_inside_sector(t_data *d, uint16_t sect_to_scan, double dist)
{
	t_sprite_list	*tmp;
	t_vec2f			pos;
	t_m16_inf		inf;

	tmp = d->sectors[sect_to_scan].sprite_list;
	inf.id_of_monst = -1;
	inf.dist = dist;
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
				if (d->monsters[tmp->id].can_collide && (dist == -1 || get_vec2f_length(sub_vec2f(vec3to2(d->cam.pos), d->monsters[tmp->id].pos)) < dist))
				{
					inf.id_of_monst = tmp->id;
					inf.dist = vec2f_length(sub_vec2f(vec3to2(d->cam.pos), d->monsters[tmp->id].pos));
				}
			}
		}
		tmp = tmp->next;
	}
	return (inf);
}

t_m16_inf	m16_recur(t_data *d, uint8_t depth, uint16_t sect_to_scan,
		uint16_t old_sect)
{
	short	i;
	short	j;
	double	dist[2];
	t_m16_inf inf;

	dist[0] = find_closest_wall_dist(d, sect_to_scan);
	i = d->sectors[sect_to_scan].firstwallnum;
	j = d->sectors[sect_to_scan].firstwallnum + d->sectors[sect_to_scan].numwalls - 1;
	inf = m16_inside_sector(d, sect_to_scan, dist[0]);
	if (inf.id_of_monst != -1)
		return (inf);
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
						return (m16_recur(d, depth - 1, d->walls[j].neighborsect, sect_to_scan));
					}
			}
			j = i;
			i++;
		}
	return (inf);
}

void	set_projectile_visual_collided_m16(t_data *d, short i, t_m16_inf inf)
{
	t_vec2f	tmp;

	tmp.x = inf.dist;
	tmp.y = 0.0;
	actualize_dir(d->cam.rot + M_PI, &tmp);
	tmp.x = d->cam.sin * inf.dist + d->cam.pos.x;
	tmp.y = d->cam.cos * inf.dist + d->cam.pos.z;
	d->projectiles[i].is_active = true;
	d->projectiles[i].id_type = M16;
	d->projectiles[i].dir.z = 0.0;
	d->projectiles[i].dir.y = 0.0; 
	d->projectiles[i].dir.x = 0.0;
	d->projectiles[i].current_anim_playing = d->projectile_type[M16].anim_order[0];
	d->projectiles[i].pos = (t_vec3f){tmp.x,
	inf.dist * Y_OFFSET_TO_ROT * d->cam.y_offset,
	tmp.y
	};
	d->projectiles[i].has_collided = true;
//	if (inf.id_of_monst != -1)
		d->projectiles[i].cursectnum = d->monsters[inf.id_of_monst].cursectnum;
//	else
//		d->projectiles[i].cursectnum = d->cursectnum;
	d->projectiles[i].time_remaining_anim = 5;
	d->projectiles[i].current_anim_playing = 0;
	d->projectiles[i].weapon_id = d->player.current_weapon;
}

void	m16_create_projectile(t_data *d, t_m16_inf inf)
{
	t_sprite_list	*new_projectile;
	short			i;
	
	i = 0;
	while (i < MAX_PROJECTILES && d->projectiles[i].is_active)
		i++;
	if (i == MAX_PROJECTILES)
		return ; //pansement (exceed size of stack so no projectile is created)
	if (!(new_projectile = malloc(sizeof(*new_projectile))))
	{
		ft_putendl_fd("malloc has failed\n", 2);
		exit(EXIT_FAILURE);
	}
	new_projectile->id = i;
	new_projectile->type = IS_PROJECTILE;
	set_projectile_visual_collided_m16(d, i, inf);
//	if (inf.id_of_monst == -1)
//	{
//		new_projectile->next = d->sectors[d->cursectnum].sprite_list;
//		d->sectors[d->cursectnum].sprite_list = new_projectile;
//	}
//	else
	{
		new_projectile->next = d->sectors[d->monsters[inf.id_of_monst].cursectnum].sprite_list;
		d->sectors[d->monsters[inf.id_of_monst].cursectnum].sprite_list = new_projectile;
	}
}

void	m16_shoot(t_data *d)
{
	t_m16_inf	inf;

	inf = m16_recur(d, 30, d->cursectnum, -1);
	if (inf.id_of_monst != -1)
	{
		monster_hit(d, M16_DAMAGE, inf.id_of_monst);
		inf.dist -= 0.1;
		m16_create_projectile(d, inf);
	}
}
