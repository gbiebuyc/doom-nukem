/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_e.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 05:20:47 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/29 19:07:17 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define ACTIVATION_DIST 1.5

bool	pickup_asset(t_data *d)
{
	int			i;
	t_assets	*asset;

	i = -1;
	while (d->nb_assets && ++i < d->assets[d->cursectnum][0].nb_assets)
	{
		asset = &d->assets[d->cursectnum][i];
		if (vec2f_length(sub_vec2f(vec3to2(d->cam.pos), asset->world_pos)) <
				ACTIVATION_DIST && !asset->used &&
				(asset->is_interactive || asset->is_autopick ||
				asset->is_key || asset->is_jetpack))
		{
			use_asset(d, asset);
			return (true);
		}
	}
	return (false);
}

void	press_e(t_data *d)
{
	if (pickup_asset(d))
		return ;
	else if (activate_door(d, &d->sectors[d->cursectnum]))
		return ;
}
