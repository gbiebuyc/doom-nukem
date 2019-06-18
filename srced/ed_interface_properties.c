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

void		draw_selection_arround_asset(t_data *d, t_vec2f *category_pos)
{
	int		x;
	int		y;
	t_vec2f	v;

	v = d->mouse;
	if (v.x + 1 + v.y * NB_ASSET_LINE >
							d->interface.nb_asset[d->interface.category])
		return ;
	v.x = (v.x * 38) + category_pos[d->interface.category].x;
	v.y = (v.y * 36) + category_pos[d->interface.category].y;
	x = -1;
	while (++x < 32)
		putpixel(d, x + v.x, v.y, 0xffff00);
	x = -1;
	while (++x < 32)
		putpixel(d, x + v.x, v.y + 32, 0xffff00);
	y = -1;
	while (++y < 32)
		putpixel(d, v.x, y + v.y, 0xffff00);
	y = -1;
	while (++y < 32)
		putpixel(d, v.x + 32, y + v.y, 0xffff00);
	show_preview(d, d->interface.toolbar.assets);
}

/*
**	prop = d->interface.toolbar.properties
*/

static void	draw_plus_minus_btn_n_checkbox(t_data *d, SDL_Surface **prop,
														int x, int y)
{
	x = W - PROPERTIES_LIMIT * 0.35;
	y = H * 0.5 + prop[0]->h * 2 + 15;
	d->interface.btn_floor_height_pos = (t_vec2f){x, y};
	copy_surface_to_surface(prop[8], d->screen, (int[2]){x, y}, d);
	copy_surface_to_surface(prop[9], d->screen, (int[2]){x + 32, y}, d);
	y += prop[1]->h * 0.5 + 15;
	d->interface.btn_ceil_height_pos = (t_vec2f){x, y};
	copy_surface_to_surface(prop[8], d->screen, (int[2]){x, y}, d);
	copy_surface_to_surface(prop[9], d->screen, (int[2]){x + 32, y}, d);
	x = W - PROPERTIES_LIMIT + MARGIN;
	y = d->interface.tex_select[1].y + 110;
	copy_surface_to_surface(prop[10], d->screen, (int[2]){x, y - 30}, d);
	copy_surface_to_surface(prop[11], d->screen, (int[2]){x, y}, d);
	d->interface.cbox_skybox_p = (t_vec2f){d->interface.tex_select[1].x - 30,
																		y};
	copy_surface_to_surface(((d->selected_sector != -1 &&
		d->sectors[d->selected_sector].outdoor) ? prop[14] : prop[13]),
			d->screen, (int[2]){d->interface.cbox_skybox_p.x, y}, d);
	y = d->interface.tex_select[2].y + 84;
	copy_surface_to_surface(prop[12], d->screen, (int[2]){x, y}, d);
	d->interface.cbox_door_p = (t_vec2f){d->interface.tex_select[2].x, y};
	copy_surface_to_surface((((d->selectedwall && d->selectedwall->is_door) ||
		(d->hl_wall && d->hl_wall->is_door)) ? prop[14] : prop[13]), d->screen,
								(int[2]){d->interface.tex_select[2].x, y}, d);
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
*/

static void	draw_selection_case(t_data *d, SDL_Surface **prop, int x, int y)
{
	x += prop[3]->w + 9;
	d->interface.tex_select[2] = (t_vec2f){x, y + (prop[3]->h >> 1)};
	draw_texture_selection(d, x, y + (prop[3]->h >> 1));
	x = W - PROPERTIES_LIMIT + MARGIN + prop[1]->w + 9;
	y = y - prop[2]->h - prop[2]->h - (prop[3]->h >> 1) - 102;
	d->interface.tex_select[1] = (t_vec2f){x, y - 33};
	draw_texture_selection(d, x, y - 33);
	y = d->interface.tex_select[1].y - (prop[1]->h >> 1) - 16;
	d->interface.tex_select[0] = (t_vec2f){x, y};
	draw_texture_selection(d, x, y);
	x = d->interface.tex_select[2].x + 160;
	y = d->interface.tex_select[2].y - (prop[15]->h >> 1);
	d->interface.tex_select[3] = (t_vec2f){x, d->interface.tex_select[2].y};
	draw_texture_selection(d, x, d->interface.tex_select[2].y);
	copy_surface_to_surface(prop[15], d->screen, (int[2]){x - 86, y + 32}, d);
}

/*
**	draw properties from the midle of the screen to the bot
*/

void		print_properties(t_data *d, SDL_Surface **properties)
{
	int	x;
	int	y;

	y = H / 2;
	x = W - PROPERTIES_LIMIT + MARGIN;
	draw_separator(d, W - PROPERTIES_LIMIT, y - 5, 0x008800);
	copy_surface_to_surface(properties[0], d->screen, (int[2]){x, y}, d);
	y += properties[0]->h + 5;
	x = W - PROPERTIES_LIMIT + MARGIN;
	copy_surface_to_surface(properties[1], d->screen, (int[2]){x, y + 5}, d);
	y += properties[0]->h + properties[1]->h + 16 + 80;
	x = W - PROPERTIES_LIMIT + MARGIN;
	draw_separator(d, W - PROPERTIES_LIMIT, y - 5, 0x008800);
	copy_surface_to_surface(properties[2], d->screen, (int[2]){x, y + 5}, d);
	y += properties[2]->h + 5;
	x = W - PROPERTIES_LIMIT + MARGIN;
	copy_surface_to_surface(properties[3], d->screen, (int[2]){x, y + 32}, d);
	draw_selection_case(d, properties, x, y);
	fill_texture_selection(d, &d->interface, ((d->selected_wall == -1 &&
				d->hl_wall) ? d->hl_wallnum : d->selected_wall));
	draw_plus_minus_btn_n_checkbox(d, d->interface.toolbar.properties, 0, 0);
}
