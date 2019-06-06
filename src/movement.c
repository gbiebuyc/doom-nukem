/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:04:53 by nallani           #+#    #+#             */
/*   Updated: 2019/06/07 00:10:18 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

# define MINIMUM_HEIGHT_TO_WALK 0.2
#define MOVE_SPEED 0.02
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
		if (neighbor != -1 && d->doorstate[i] > 0.7)
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

# define MONSTER_MIN_DIST_HITBOX 0.15

t_vec3f	update_pos_vec3f(t_vec3f old_pos, t_vec3f new_pos, t_vec2f point, double radius)
{
	t_vec2f		tmp[2];
	double		angle;
	(void)old_pos;
	(void)new_pos;
	(void)point;
	(void)radius;

	tmp[0].x = new_pos.x - point.x;
	tmp[0].y = new_pos.z - point.y;
	tmp[1].x = radius;
	tmp[1].y = 0.0;
	angle = atan2(tmp[0].y, tmp[0].x);
	actualize_dir(angle, &tmp[1]);
	new_pos.x = tmp[1].x + point.x;
	new_pos.z = tmp[1].y + point.y;

	return (new_pos);
}

void	collision_with_monster(t_data *d, short	cur_sect, t_vec3f old_pos)
{
	t_sprite_list	*tmp;
//	t_vec2f			result_coll;
//	short			i;// used for sector loop

	tmp = d->sectors[cur_sect].sprite_list;
	while (tmp)
	{
		if (tmp->type == IS_MONSTER && d->monsters[tmp->id].can_collide)
		{
			if (vec2f_length(sub_vec2f(d->monsters[tmp->id].pos, (t_vec2f){d->cam.pos.x, d->cam.pos.z})) <
					d->monster_type[d->monsters[tmp->id].id_type].hitbox_radius + MONSTER_MIN_DIST_HITBOX)
				d->cam.pos = update_pos_vec3f(old_pos, d->cam.pos, d->monsters[tmp->id].pos,
						d->monster_type[d->monsters[tmp->id].id_type].hitbox_radius + MONSTER_MIN_DIST_HITBOX);
		}
		if (tmp->type == IS_PROJECTILE && d->projectile_type[d->projectiles[tmp->id].id_type].threat_to_player)
			if (vec3f_length(sub_vec3f(d->cam.pos, d->projectiles[tmp->id].pos)) <
					PLAYER_HITBOX + d->projectile_type[d->projectiles[tmp->id].id_type].hitbox_radius)
			{
				;//player got hit
			}
		tmp = tmp->next;
	}
}

void	inertia(t_data *d, t_vec2f mvt);
void	movement(t_data *d)
{
	t_vec3f	old_pos;
	t_vec2f	mvt;
	short	count;

	count = 0;
	ft_bzero(&mvt, sizeof(t_vec2f));
	old_pos = d->cam.pos;
	if (d->keys[SDL_SCANCODE_W] && ++count)
	{
		mvt.y += d->cam.cos * MOVE_SPEED;
		mvt.x += d->cam.sin * MOVE_SPEED;
	}
	if (d->keys[SDL_SCANCODE_S] && ++count)
	{
		mvt.y -= d->cam.cos * MOVE_SPEED;
		mvt.x -= d->cam.sin * MOVE_SPEED;
	}
	if (d->keys[SDL_SCANCODE_A] && ++count)
	{
		mvt.y += d->cam.sin * MOVE_SPEED;
		mvt.x -= d->cam.cos * MOVE_SPEED;
	}
	if (d->keys[SDL_SCANCODE_D] && ++count)
	{
		mvt.y -= d->cam.sin * MOVE_SPEED;
		mvt.x += d->cam.cos * MOVE_SPEED;
	}
	if (count == 2)
		mvt = mul_vec2f(mvt,  0.707); // 1 / sqrt(2)
	inertia(d, mvt);
	d->cam.pos.z += d->inertia.y;
	d->cam.pos.x += d->inertia.x;
	d->cam.pos.y += d->keys[SDL_SCANCODE_SPACE] * MOVE_SPEED;
	d->cam.pos.y -= d->keys[SDL_SCANCODE_LSHIFT] * MOVE_SPEED;
	while (collision(d, d->cursectnum))
		;
	collision_with_monster(d, d->cursectnum, old_pos);
}
