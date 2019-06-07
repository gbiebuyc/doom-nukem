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

void	init_structure(t_data *d)
{
	ft_memset(d, 0, sizeof(t_data));
	d->scale = W / 64;
	d->pos = (t_vec2f){0, 0};
	d->selectedwall = NULL;
	d->selectedwall2 = NULL;
	d->grid_locking = true;
	d->sectordrawing = false;
	d->interface.show_menu = 0;
	d->interface.select = 1;
	d->interface.move = 0;
	d->texture_to_scale = -1;
	d->interface.texture_case_select = -1;
	d->selected_texture = -2;
	d->interface.category = -1;
	d->interface.selected_asset = -1;
	d->interface.separate_sector = 0;
	d->default_texture = 0;
}

void	init_sectors(t_data *d)
{
	int		dt;

	dt = d->default_texture;
	d->sectors[0] = (t_sector){0, 4, 0, 1, dt, dt,
		1.0, false, "", "", false, NULL};
	d->walls[0] = (t_wall){(t_vec2f){-2, 2}, dt, dt, dt, 0, -1, "", false};
	d->walls[1] = (t_wall){(t_vec2f){ 2, 2}, dt, dt, dt, 0, -1, "", false};
	d->walls[2] = (t_wall){(t_vec2f){ 2, -2}, dt, dt, dt, 0, -1, "", false};
	d->walls[3] = (t_wall){(t_vec2f){-2, -2}, dt, dt, dt, 0, -1, "", false};
	d->numsectors = 1;
	d->numwalls = 4;
	d->player_start = (t_vec3f){0, 0, 0};
}

void	init_monsters(t_data *d)
{
	t_monster	monster;
	t_vec2f		pos;

	pos.x = 0.0;
	pos.y = -3.0;
	d->nummonsters = 1;
	monster.pos = pos;
	monster.activated = true;
	monster.rot = 0.0;
	monster.health_mult = 1;
	monster.id_type = MOTHERDEMON;
	monster.size = 1.0;
	monster.cursectnum = 0;
	d->monsters[0] = monster;
//	monster.behavior = &basic_monster;
}
