/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_interface_properties.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 03:57:24 by mikorale          #+#    #+#             */
/*   Updated: 2019/05/17 03:57:28 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
**	prop[16] = lblEnd.bmp
**	prop[17] = lblNextmap.bmp
**	prop[18] = browseBox.bmp
*/

static void	draw_cbend_n_nextmap(t_data *d, SDL_Surface **prop, int x, int y)
{
	x = d->interface.cbox_skybox_p.x + 45;
	y = d->interface.cbox_skybox_p.y;
	copy_surface_to_surface(prop[16], d->screen, (int[2]){x, y + 3}, d);
	d->interface.cbox_end_p = (t_vec2){x + prop[16]->w + 15, y};
	copy_surface_to_surface(((d->selected_sector != -1 &&
			d->sectors[d->selected_sector].is_finish) ? prop[14] : prop[13]),
			d->screen, (int[2]){d->interface.cbox_end_p.x, y}, d);
	x = W - PROPERTIES_LIMIT + 8;
	y = d->interface.cbox_end_p.y + 40;
	copy_surface_to_surface(prop[17], d->screen, (int[2]){x, y}, d);
	d->interface.box_nex_map_p =
			(t_vec2){x + d->interface.toolbar.properties[17]->w + 10, y};
}

/*
**	prop = d->interface.toolbar.properties
**	prop[8] = minus.bmp // button
**	prop[9] = plus.bmp // button
**	prop[10] = lblLight.bmp // lbl = Label
**	prop[11] = lblSkybox.bmp
**	prop[12] = lblDoor.bmp
**	prop[13] = check_box_empty.bmp
**	prop[14] = check_box.bmp
*/

static void	draw_plus_minus_btn_n_checkbox(t_data *d, SDL_Surface **prop,
														int x, int y)
{
	x = W - PROPERTIES_LIMIT + prop[1]->w + 70;
	y = PROPERTIES_POS + prop[0]->h * 2 + 18;
	d->interface.btn_ceil_height_pos = (t_vec2){x, y};
	copy_surface_to_surface(prop[8], d->screen, (int[2]){x, y}, d);
	copy_surface_to_surface(prop[9], d->screen, (int[2]){x + 32, y}, d);
	y += prop[1]->h * 0.5 + 17;
	d->interface.btn_floor_height_pos = (t_vec2){x, y};
	copy_surface_to_surface(prop[8], d->screen, (int[2]){x, y}, d);
	copy_surface_to_surface(prop[9], d->screen, (int[2]){x + 32, y}, d);
	x = W - PROPERTIES_LIMIT + MARGIN;
	y = d->interface.tex_select[1].y + 110;
	copy_surface_to_surface(prop[10], d->screen, (int[2]){x, y - 33}, d);
	copy_surface_to_surface(prop[11], d->screen, (int[2]){x, y}, d);
	d->interface.cbox_skybox_p = (t_vec2){x + prop[11]->w + 15, y};
	copy_surface_to_surface(((d->selected_sector != -1 &&
			d->sectors[d->selected_sector].outdoor) ? prop[14] : prop[13]),
			d->screen, (int[2]){d->interface.cbox_skybox_p.x, y}, d);
	y = d->interface.tex_select[2].y + 74;
	copy_surface_to_surface(prop[12], d->screen, (int[2]){x, y}, d);
	d->interface.cbox_door_p = (t_vec2){x + prop[12]->w + 15, y};
	copy_surface_to_surface((((d->selectedwall && d->selectedwall->is_door) ||
		(d->hl_wall && d->hl_wall->is_door)) ? prop[14] : prop[13]), d->screen,
								(int[2]){d->interface.cbox_door_p.x, y}, d);
	draw_cbend_n_nextmap(d, prop, x, y);
}

/*
**	hv = horizontal_vertical (0 = h, 1 = V)
*/

static void	draw_texture_selection(t_data *d, int x, int y)
{
	int i;
	int	x_tmp;
	int	y_tmp;

	x_tmp = x;
	y_tmp = y;
	i = -1;
	while (++i < 66)
		putpixel(d, x++, y, 0x008800);
	i = -1;
	x = x_tmp;
	y = y_tmp;
	while (++i < 66)
		putpixel(d, x++, y + 66, 0x008800);
	i = -1;
	x = x_tmp;
	y = y_tmp;
	while (++i < 66)
		putpixel(d, x, y++, 0x008800);
	i = -1;
	x = x_tmp;
	y = y_tmp;
	while (++i < 66)
		putpixel(d, x + 66, y++, 0x008800);
}

/*
**	"prop" -> "properties"
**	Draw the case to handle visual texture selection,
**	starting with the most down case.
**	keep drawing from bot to niddle of the screen.
**	prop[15] = lblPoster.bmp
*/

static void	draw_selection_case(t_data *d, SDL_Surface **prop, int x, int y)
{
	x += prop[3]->w + 9;
	d->interface.tex_select[2] = (t_vec2f){x, y + (prop[3]->h >> 1)};
	draw_texture_selection(d, x, y + (prop[3]->h >> 1));
	x = W - PROPERTIES_LIMIT + MARGIN + prop[1]->w + 9;
	y = y - prop[2]->h - prop[2]->h - (prop[3]->h >> 1) - 102 - MOVE_WALL_PROP;
	d->interface.tex_select[1] = (t_vec2f){x, y - 33};
	draw_texture_selection(d, x, y - 33);
	y = d->interface.tex_select[1].y - (prop[1]->h >> 1) - 16;
	d->interface.tex_select[0] = (t_vec2f){x, y};
	draw_texture_selection(d, x, y);
	x = d->interface.tex_select[2].x + 100;
	y = d->interface.tex_select[2].y - prop[15]->h;
	d->interface.tex_select[3] = (t_vec2f){x, d->interface.tex_select[2].y};
	draw_texture_selection(d, x, d->interface.tex_select[3].y);
	copy_surface_to_surface(prop[15], d->screen, (int[2]){x - 20, y}, d);
}

/*
**	draw properties from the midle of the screen to the bot
**	properties[0] = lblsector, properties[1] = sector_info,
**	properties[2] = lblWall, properties[3] = lblTexture
*/

void		print_properties(t_data *d, SDL_Surface **properties, int x, int y)
{
	x = W - PROPERTIES_LIMIT + MARGIN;
	draw_separator(d, W - PROPERTIES_LIMIT, y - 5, 0x008800);
	copy_surface_to_surface(properties[0], d->screen, (int[2]){x, y}, d);
	y += properties[0]->h + 5;
	x = W - PROPERTIES_LIMIT + MARGIN;
	copy_surface_to_surface(properties[1], d->screen, (int[2]){x, y + 5}, d);
	y += properties[0]->h + properties[1]->h + 16 + 80 + MOVE_WALL_PROP;
	x = W - PROPERTIES_LIMIT + MARGIN;
	draw_separator(d, W - PROPERTIES_LIMIT, y - 5, 0x008800);
	copy_surface_to_surface(properties[2], d->screen, (int[2]){x, y + 5}, d);
	y += properties[2]->h + 5;
	x = W - PROPERTIES_LIMIT + MARGIN;
	copy_surface_to_surface(properties[3], d->screen, (int[2]){x, y + 32}, d);
	draw_selection_case(d, properties, x, y);
	if (d->numwalls > 0 && d->numsectors > 0)
		fill_texture_selection(d, &d->interface, ((d->selected_wall == -1 &&
				d->hl_wall) ? d->hl_wallnum : d->selected_wall), 0);
	draw_plus_minus_btn_n_checkbox(d, d->interface.toolbar.properties, 0, 0);
	x = W - PROPERTIES_LIMIT + MARGIN;
	y = d->interface.cbox_door_p.y + 30;
	d->interface.cbox_transparent_p = (t_vec2){x + properties[20]->w - 24, y};
	copy_surface_to_surface(properties[20], d->screen, (int[2]){x, y - 2}, d);
	if (d->hl_wallnum != -1 && d->walls[d->hl_wallnum].is_transparent)
		copy_surface_to_surface(properties[14], d->screen,
						(int[2]){d->interface.cbox_transparent_p.x, y + 1}, d);
}
