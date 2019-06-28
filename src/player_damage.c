/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_damage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 23:46:25 by nallani           #+#    #+#             */
/*   Updated: 2019/06/28 18:15:59 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MINIMUM_CROUCH_HEIGHT 0.2

void	player_fell(t_data *d)
{
	d->player.gravity = fabs(d->player.gravity);
	d->player.minimum_height = MINIMUM_CROUCH_HEIGHT;
	change_buf_colo(d, d->player.gravity * 100, 0x111111);
	d->player.can_move = d->player.gravity > 0.2 ? 40 : 20;
	d->player.health -= 10;
	d->player.gravity = 0.0;
}

# define BOUNCING_DIST_PROJ 0.12
# define BOUNCING_DIST_MOTHERDEMON 0.15
# define BOUCING_DIST_CHARGINGDEMON 0.23

void	player_hit_projectile(t_data *d, t_projectile *projectile)
{
	change_buf_colo(d, d->projectile_type[projectile->id_type].damage, RED);
	if (projectile)
		change_inertia(d, atan2(projectile->dir.z,
			projectile->dir.x), BOUNCING_DIST_PROJ);
	d->player.health -= d->projectile_type[projectile->id_type].damage;
}

void	check_dangerous_area(t_data *d)
{
	if (!d->sectors[d->cursectnum].is_harmful)
		return ;
	if (fabs(d->cam.pos.y - MINIMUM_HEIGHT - d->floorheightplayer) > 0.1)
		return ;
	if (SDL_GetTicks() - d->last_dangerous_area_damage < 1000)
		return ;
	change_buf_colo(d, 7, RED);
	d->player.health -= 20;
	d->last_dangerous_area_damage = SDL_GetTicks();
}

void		player_contact_monster(t_data *d, t_monster *monster)
{
	if (monster->id_type == MOTHERDEMON)
	{
		if (!d->player.can_be_stomped)
		{
			d->player.health -= 5;
			d->player.can_be_stomped = 30;
			change_buf_colo(d, 5, RED);
		}
		change_inertia(d, atan2(monster->dir.y, monster->dir.x),
				BOUNCING_DIST_MOTHERDEMON);
	}
	if (monster->id_type == CHARGINGDEMON)
	{
		if (!d->player.can_be_stomped)
		{
			d->player.health -= 15;
			d->player.can_be_stomped = 30;
//			change_buf_colo(d, 8, RED);
		}
		change_inertia(d, atan2(monster->dir.y, monster->dir.x),
				BOUCING_DIST_CHARGINGDEMON);		
		charging_demon_wait(d, monster);
	}
}
