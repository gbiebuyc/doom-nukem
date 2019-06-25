/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:04:53 by nallani           #+#    #+#             */
/*   Updated: 2019/06/26 00:40:45 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MINIMUM_HEIGHT_TO_WALK 0.32
#define MOVE_SPEED 0.02
#define MINIMUM_HEIGHT_OF_WALKABLE_SECTOR 0.6
#define MINIMUM_CEIL_DIST 0.1
#define MONSTER_MIN_DIST_HITBOX 0.15

t_vec3f	update_pos_vec3f(t_vec3f old_pos,
		t_vec3f new_pos, t_vec2f point, double radius)
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

void	collision_with_monster(t_data *d, short cur_sect, t_vec3f old_pos)
{
	t_sprite_list	*tmp;

	tmp = d->sectors[cur_sect].sprite_list;
	while (tmp)
	{
		if (tmp->type == IS_MONSTER && d->monsters[tmp->id].can_collide)
		{
			if (vec2f_length(sub_vec2f(d->monsters[tmp->id].pos, (t_vec2f)
				{d->cam.pos.x, d->cam.pos.z})) < d->monster_type[d->monsters[
					tmp->id].id_type].hitbox_radius + MONSTER_MIN_DIST_HITBOX)
				d->cam.pos = update_pos_vec3f(old_pos, d->cam.pos,
				d->monsters[tmp->id].pos, d->monster_type[d->monsters[tmp->
				id].id_type].hitbox_radius + MONSTER_MIN_DIST_HITBOX);
		}
		if (tmp->type == IS_PROJECTILE && d->projectile_type[d->
				projectiles[tmp->id].id_type].threat_to_player)
			if (vec3f_length(sub_vec3f(d->cam.pos, d->projectiles[tmp->
				id].pos)) < PLAYER_HITBOX + d->projectile_type[d->
				projectiles[tmp->id].id_type].hitbox_radius)
			{
			}
		tmp = tmp->next;
	}
}

void	mvtnallanicaca(t_data *d, short *count, t_vec2f *mvt)
{
	if (d->keys[SDL_SCANCODE_W] && ++*count)
	{
		mvt->y += d->cam.cos * MOVE_SPEED;
		mvt->x += d->cam.sin * MOVE_SPEED;
	}
	if (d->keys[SDL_SCANCODE_S] && ++*count)
	{
		mvt->y -= d->cam.cos * MOVE_SPEED;
		mvt->x -= d->cam.sin * MOVE_SPEED;
	}
	if (d->keys[SDL_SCANCODE_A] && ++*count)
	{
		mvt->y += d->cam.sin * MOVE_SPEED;
		mvt->x -= d->cam.cos * MOVE_SPEED;
	}
	if (d->keys[SDL_SCANCODE_D] && ++*count)
	{
		mvt->y -= d->cam.sin * MOVE_SPEED;
		mvt->x += d->cam.cos * MOVE_SPEED;
	}
	if (*count == 2)
		*mvt = mul_vec2f(*mvt, 0.707);
	inertia(d, *mvt);
}

void	movement(t_data *d)
{
	t_vec3f	old_pos;
	t_vec2f	mvt;
	short	count;

	old_pos = d->cam.pos;
	if (!d->player.can_move)
	{
		count = 0;
		ft_bzero(&mvt, sizeof(t_vec2f));
		mvtnallanicaca(d, &count, &mvt);
		d->cam.pos.z += d->inertia.y;
		d->cam.pos.x += d->inertia.x;
	}
	else
		d->player.can_move--;
	d->floorheightplayer = get_floorheight_player(d, d->cursectnum);
	d->ceilheightplayer = get_ceilheight_player(d, d->cursectnum);
	while (collision(d, &d->sectors[d->cursectnum]))
		;
	collision_with_monster(d, d->cursectnum, old_pos);
}
