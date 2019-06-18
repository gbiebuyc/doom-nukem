/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_damage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 23:46:25 by nallani           #+#    #+#             */
/*   Updated: 2019/06/10 00:03:21 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

# define MINIMUM_CROUCH_HEIGHT 0.2// defined in jump too

void	player_fell(t_data *d)
{
	d->player.gravity = fabs(d->player.gravity);
	d->player.minimum_height = MINIMUM_CROUCH_HEIGHT;
	change_buf_colo(d, d->player.gravity * 100 /*wtf value*/, 0x111111);
	d->player.can_move = d->player.gravity > 0.2 ? 40 : 20;
	d->player.health -= 10;
}

# define BOUNCING_DIST_PROJ 0.12

void		player_hit_projectile(t_data *d, t_projectile *projectile)
{
	change_buf_colo(d, d->projectile_type[projectile->id_type].damage, RED);
	if (projectile)
		change_inertia(d, atan2(projectile->dir.z, projectile->dir.x), BOUNCING_DIST_PROJ);
	d->player.health -= 10;
}
