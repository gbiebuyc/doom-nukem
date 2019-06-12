/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_init_structures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 16:20:23 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/07 16:20:24 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		init_data(t_data *d)
{
	ft_memset(d, 0, sizeof(t_data));
	*d = (t_data){.win = NULL, .screen = NULL, .textures = NULL,
		.texture_list = NULL, .pos = {0, 0}, .startsectnum = 0,
		.monsters = NULL, .nbmonsters = 0, .scale = W >> 6,
		.selectedwall = NULL, .selectedwall2 = NULL, .grid_locking = true,
		.sectordrawing = false, .default_texture = 0, .selected_texture = -2};
	d->player_start = (t_vec3f){0, 0.2, 0};
	d->interface.show_menu = 0;
	d->interface.select = 1;
	d->interface.move = 0;
	d->texture_to_scale = -1;
	d->interface.texture_case_select = -1;
	d->interface.category = -1;
	d->interface.selected_asset = -1;
	d->interface.separate_sector = 0;
	d->interface.monster_list = NULL;
	d->startsectnum = 0;
}

void		init_sectors(t_data *d)
{
	int		dt;

	dt = d->default_texture;
	d->sectors[0] = (t_sector){0, 4, 0, 1, dt, dt,
		1.0, false, "", "", false, NULL, 0};
	d->walls[0] = (t_wall){(t_vec2f){-4, 4}, dt, dt, dt, 0, -1, "", false};
	d->walls[1] = (t_wall){(t_vec2f){4, 4}, dt, dt, dt, 0, -1, "", false};
	d->walls[2] = (t_wall){(t_vec2f){4, -4}, dt, dt, dt, 0, -1, "", false};
	d->walls[3] = (t_wall){(t_vec2f){-4, -4}, dt, dt, dt, 0, -1, "", false};
	d->numsectors = 1;
	d->numwalls = 4;
}
