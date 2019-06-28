/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:04:53 by nallani           #+#    #+#             */
/*   Updated: 2019/06/28 17:18:06 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MINIMUM_HEIGHT_TO_WALK 0.32
#define MOVE_SPEED 0.02
#define MINIMUM_HEIGHT_OF_WALKABLE_SECTOR 0.6
#define MINIMUM_CEIL_DIST 0.1

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
	if (d->player.can_be_stomped)
		d->player.can_be_stomped--;
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
	collision_with_monster(d, d->cursectnum);
}
