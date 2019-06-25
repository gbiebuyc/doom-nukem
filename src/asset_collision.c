/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 14:45:42 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/23 14:45:42 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define COLLISION_R 0.8

void	use_asset(t_data *d, t_assets *asset)
{
	d->player.health += asset->stat_mod.heal;
	d->player.health -= asset->stat_mod.damage;
	d->player.is_flying += asset->is_jetpack ? 10000 : 0;
	if (!d->slot1)
		d->slot1 = asset;
	else if (!d->slot2)
		d->slot2 = asset;
	else if (!d->slot3)
		d->slot3 = asset;
	else
		return (invoke_msg(d, "INVENTORY IS FULL"));
	asset->used = true;
}

void	asset_collision2(t_data *d, t_assets *asset)
{
	t_vec2f	dist;
	double	dist_len;

	if (asset->used || asset->is_on_ceil)
		return ;
	dist = sub_vec2f(vec3to2(d->cam.pos), asset->world_pos);
	dist_len = vec2f_length(dist);
	if (dist_len > COLLISION_R)
		return ;
	if (asset->collision)
	{
		d->cam.pos.x = asset->world_pos.x + dist.x * COLLISION_R / dist_len;
		d->cam.pos.z = asset->world_pos.y + dist.y * COLLISION_R / dist_len;
	}
	if (asset->is_autopick)
		use_asset(d, asset);
}

void	asset_collision(t_data *d)
{
	int i;

	i = -1;
	while (d->nb_assets && ++i < d->assets[d->cursectnum][0].nb_assets)
	{
		asset_collision2(d, &d->assets[d->cursectnum][i]);
	}
}
