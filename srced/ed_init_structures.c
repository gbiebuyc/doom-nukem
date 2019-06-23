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
	*d = (t_data){.font = {C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11,
		C12, C13, C14, C15, C16, C17, C18, C19, C20, C21, C22, C23, C24, C25,
		C26, C27, C28, C29, C30, C31, C32, C33, C34, C35, C36, C37, C38, C39,
		C40, C41, C42, C43, C44, C45, C46, C47}, .win = NULL, .screen = NULL,
		.textures = NULL, .texture_list = NULL, .pos = {0, 0}, .nb_texture = 0,
		.startsectnum = 0, .monsters = NULL, .nbmonsters = 0, .scale = W >> 6,
		.selectedwall = NULL, .selectedwall2 = NULL, .grid_locking = true,
		.sectordrawing = false, .default_wall_texture = 0, .nb_assets = 0,
		.default_floor_texture = 0, .default_ceil_texture = 0, .nb_posters = 0,
		.selected_texture = -2, .map_to_open = NULL, .texture_to_scale = -1,
		.current_loaded_map = "newmap.DNMAP", .get_next_map = 0, .nb_door = 0,
		.nb_keys = 0, .assets = NULL};
	d->player_start = (t_vec3f){0, 0.2, 0};
	d->startsectnum = 0;
	d->interface = (t_interface){.show_menu = 0, .select = 1, .move = 0,
			.texture_case_select = -1, .category = -1, .selected_asset = -1,
			.separate_sector = 0, .monster_list = NULL, .map_list = NULL,
			.map_list_sort = NULL, .prompt_map_open = 0, .selected_map = -1,
			.assets_list = NULL};
	ft_memset(d->next_map, 0, 100);
}

void		init_sectors(t_data *d)
{
	int		dt;

	dt = d->default_floor_texture;
	d->sectors[0] = (t_sector){0, 4, 0, 1, dt, dt,
		1.0, false, "", "", false, NULL, 0, 0, 0, 0, false, false};
	d->walls[0] = (t_wall){(t_vec2f){-4, 4}, dt, dt, dt, 0, -1, "", false, -1,
		0, -1, false};
	d->walls[1] = (t_wall){(t_vec2f){4, 4}, dt, dt, dt, 0, -1, "", false, -1,
		0, -1, false};
	d->walls[2] = (t_wall){(t_vec2f){4, -4}, dt, dt, dt, 0, -1, "", false, -1,
		0, -1, false};
	d->walls[3] = (t_wall){(t_vec2f){-4, -4}, dt, dt, dt, 0, -1, "", false, -1,
		0, -1, false};
	d->numsectors = 1;
	d->numwalls = 4;
}

static void	assign_position(t_vec2 *btn, t_vec2 pos)
{
	*btn = pos;
}

void		init_button_position(t_data *d, int x, int y, t_btn_option_p *b)
{
	y = H - d->interface.toolbar.properties[6]->h + 38;
	assign_position(&b->cbox_onfloor, (t_vec2){93, y});
	x = 215;
	assign_position(&b->cbox_onceil, (t_vec2){x, y});
	assign_position(&b->btn_restorehp_minus, (t_vec2){x, y += 33});
	assign_position(&b->btn_restorehp_plus, (t_vec2){x + 30, y});
	assign_position(&b->btn_damaehp_minus, (t_vec2){x, y += 30});
	assign_position(&b->btn_damaehp_plus, (t_vec2){x + 30, y});
	assign_position(&b->btn_ammo_ballista_minus, (t_vec2){x, y += 30});
	assign_position(&b->btn_ammo_ballista_plus, (t_vec2){x + 30, y});
	assign_position(&b->btn_ammo_blaster_minus, (t_vec2){x, y += 30});
	assign_position(&b->btn_ammo_blaster_plus, (t_vec2){x + 30, y});
	assign_position(&b->btn_ammo_m16_minus, (t_vec2){x, y += 30});
	assign_position(&b->btn_ammo_m16_plus, (t_vec2){x + 30, y});
	assign_position(&b->cbox_isinteractive, (t_vec2){x, y += 30});
	assign_position(&b->cbox_autopickup, (t_vec2){x, y += 30});
	assign_position(&b->cbox_collision, (t_vec2){x, y += 30});
	assign_position(&b->cbox_jetpack, (t_vec2){x, y += 30});
	assign_position(&b->cbox_key, (t_vec2){x, y += 30});
}
