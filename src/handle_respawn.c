/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_respawn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 22:11:51 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/30 12:29:51 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	reset_assets(t_data *d)
{
	int i;
	int j;

	i = -1;
	while (d->nb_assets && ++i < d->numsectors)
	{
		j = -1;
		while (++j < d->assets[i][0].nb_assets)
			d->assets[i][j].used = false;
	}
}

void	handle_respawn(t_data *d)
{
	play_sound(d, PLAYER_DEATH_SOUND, vec3to2(d->cam.pos));
	init_monsters(d);
	init_player(d, &d->player);
	reset_assets(d);
	invoke_msg(d, "YOU DIED");
}
