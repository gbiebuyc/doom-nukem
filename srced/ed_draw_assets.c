/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_draw_assets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 17:46:34 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/01 17:46:35 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_assets_to_map(t_data *d)
{
	t_vec2f	p;

	p = worldtoscreen(d, (t_vec2f){d->player_start.x, d->player_start.z});
	copy_surface_to_surface(d->interface.toolbar.player_start, d->screen,
							(int[2]){p.x - 16, p.y - 16}, d);
	// TODO monsters assets + select assets on the map + delete
	// + MOVE assets options
}
