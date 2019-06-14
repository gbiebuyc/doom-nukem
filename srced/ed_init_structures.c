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
	init_font(d);
	*d = (t_data){.font = {C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11,
		C12, C13, C14, C15, C16, C17, C18, C19, C20, C21, C22, C23, C24, C25,
		C26, C27, C28, C29, C30, C31, C32, C33, C34, C35, C36, C37, C38, C39,
		C40, C41, C42, C43, C44, C45, C46, C47}, .win = NULL, .screen = NULL,
		.textures = NULL, .texture_list = NULL, .pos = {0, 0},
		.startsectnum = 0, .monsters = NULL, .nbmonsters = 0, .scale = W >> 6,
		.selectedwall = NULL, .selectedwall2 = NULL, .grid_locking = true,
		.sectordrawing = false, .default_texture = 0, .selected_texture = -2,
		.open_map_path = NULL, .current_loaded_map = "./maps/newmap.DNMAP"};
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
	d->interface.map_list = NULL;
	d->interface.prompt_map_open = 0;
	d->interface.selected_map = -1;
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
