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

void		show_preview(t_data *d, t_assets *a)
{
	int	n;
	int	x;
	int	y;

	n = d->temp.x + d->temp.y * 7;
	if (d->interface.category < 3)
	{
		x = d->interface.mouse_pos.x + 10;
		y = d->interface.mouse_pos.y + 10;
		copy_surface_to_surface(a[d->interface.category].assets[n], d->screen,
															(int[2]){x, y}, d);
	}
}

void		draw_selection_arround_asset(t_data *d, t_vec2f *category_pos)
{
	int		x;
	int		y;
	t_vec2f	v;

	v = d->temp;
	if (v.x + 1 + v.y * 7 > d->interface.nb_asset[d->interface.category])
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

static void	draw_plus_minus_btn(t_data *d)
{
	int	x;
	int	y;

	x = W - PROPERTIES_LIMIT * 0.25;
	y = H * 0.5 + d->interface.toolbar.properties[0]->h * 2 + 15;
	d->interface.btn_floor_height_pos = (t_vec2f){x, y};
	copy_surface_to_surface(d->interface.toolbar.properties[8], d->screen,
													(int[2]){x, y}, d);
	copy_surface_to_surface(d->interface.toolbar.properties[9], d->screen,
													(int[2]){x + 32, y}, d);
	y += d->interface.toolbar.properties[1]->h * 0.5 + 15;
	d->interface.btn_ceil_height_pos = (t_vec2f){x, y};
	copy_surface_to_surface(d->interface.toolbar.properties[8], d->screen,
													(int[2]){x, y}, d);
	copy_surface_to_surface(d->interface.toolbar.properties[9], d->screen,
													(int[2]){x + 32, y}, d);
}

/*
**	hv = horizontal_vertical (0 = h, 1 = V)
*/

static void	draw_texture_selection(t_data *d, int x, int y, int hv)
{
	int i;

	i = -1;
	while (++i < 66)
	{
		putpixel(d, x, y, 0x008800);
		if (hv)
			x++;
		else
			y++;
	}
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
	d->interface.tex_select[2] = (t_vec2f){x, y + (prop[3]->h * 0.5)};
	draw_texture_selection(d, x, y + (prop[3]->h * 0.5), 1);
	draw_texture_selection(d, x, y + (prop[3]->h * 0.5) + 66, 1);
	draw_texture_selection(d, x, y + (prop[3]->h * 0.5), 0);
	draw_texture_selection(d, x + 66, y + (prop[3]->h * 0.5), 0);
	x = W - PROPERTIES_LIMIT + MARGIN + prop[1]->w + 9;
	y = y - prop[2]->h - prop[2]->h - prop[3]->h * 0.5 - 22;
	d->interface.tex_select[1] = (t_vec2f){x, y - 33};
	draw_texture_selection(d, x, y - 33, 1);
	draw_texture_selection(d, x, y - 33, 0);
	draw_texture_selection(d, x, y + 33, 1);
	draw_texture_selection(d, x + 66, y - 33, 0);
	y = d->interface.tex_select[1].y - prop[1]->h * 0.5 - 16;
	d->interface.tex_select[0] = (t_vec2f){x, y};
	draw_texture_selection(d, x, y, 1);
	draw_texture_selection(d, x, y, 0);
	draw_texture_selection(d, x, y + 66, 1);
	draw_texture_selection(d, x + 66, y, 0);
}

/*
**	draw properties from the midle of the screen to the bot
*/

void		print_properties(t_data *d, SDL_Surface **properties)
{
	int	x;
	int	y;

	y = H / 2;
	x = W - (PROPERTIES_LIMIT * 0.5) - (properties[0]->w * 0.5);
	draw_separator(d, W - PROPERTIES_LIMIT, y - 5, 0x008800);
	copy_surface_to_surface(properties[0], d->screen, (int[2]){x, y}, d);
	y += properties[0]->h + 5;
	x = W - PROPERTIES_LIMIT + MARGIN;
	draw_separator(d, W - PROPERTIES_LIMIT, y, 0x008800);
	copy_surface_to_surface(properties[1], d->screen, (int[2]){x, y + 5}, d);
	y += properties[0]->h + properties[1]->h + 16;
	x = W - (PROPERTIES_LIMIT * 0.5) - (properties[2]->w * 0.5);
	draw_separator(d, W - PROPERTIES_LIMIT, y - 5, 0x008800);
	copy_surface_to_surface(properties[2], d->screen, (int[2]){x, y}, d);
	y += properties[2]->h + 5;
	x = W - PROPERTIES_LIMIT + MARGIN;
	draw_separator(d, W - PROPERTIES_LIMIT, y, 0x008800);
	copy_surface_to_surface(properties[3], d->screen, (int[2]){x, y + 32}, d);
	draw_selection_case(d, properties, x, y);
	fill_texture_selection(d, &d->interface);
	draw_plus_minus_btn(d);
}
