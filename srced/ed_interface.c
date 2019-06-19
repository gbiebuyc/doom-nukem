/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_interface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 21:59:44 by mikorale          #+#    #+#             */
/*   Updated: 2019/05/14 21:59:45 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	get_category_position(t_data *d)
{
	int	x;
	int	y;

	x = W - PROPERTIES_LIMIT + 8;
	y = d->interface.toolbar.properties[4]->h + 15;
	d->interface.category_pos[0] = (t_vec2f){x - 1, y - 1};
	y = y + 40 + d->interface.toolbar.properties[5]->h + 13;
	d->interface.category_pos[1] = (t_vec2f){x, y};
	d->interface.category_pos[2] = (t_vec2f){x, y + 90 +
								d->interface.toolbar.properties[6]->h};
	y = H * 0.40 + d->interface.toolbar.properties[7]->h + 20;
	d->interface.category_pos[3] = (t_vec2f){x, y};
}

static void	print_assets(t_data *d, t_assets *a)
{
	int	m;
	int	j;
	int	x;
	int	y;

	get_category_position(d);
	m = -1;
	while (++m < 3 && (j = -1) < 0)
	{
		y = d->interface.category_pos[m].y;
		x = W - PROPERTIES_LIMIT - 30;
		d->texture_to_scale = 32;
		while (++j < d->interface.nb_asset[m])
		{
			copy_surface_to_surface(a[m].assets[j], d->screen,
										(int[2]){x += 38, y}, d);
			if (j != 0 && (j % (NB_ASSET_LINE - 1)) == 0 && (y += 36))
				x = W - PROPERTIES_LIMIT - 30;
		}
		d->texture_to_scale = -1;
	}
	x = W - PROPERTIES_LIMIT + 8;
	y = d->interface.category_pos[3].y;
	copy_surface_to_surface(d->interface.toolbar.player_start, d->screen,
													(int[2]){x, y}, d);
}

static void	print_assets_toolbar(t_data *d, SDL_Surface **prop)
{
	int	x;
	int	y;

	x = (W - PROPERTIES_LIMIT * 0.5) - prop[4]->w * 0.5;
	y = 5;
	copy_surface_to_surface(prop[4], d->screen, (int[2]){x, y}, d);
	y += prop[4]->h + 5;
	draw_separator(d, W - PROPERTIES_LIMIT, y, 0x008800);
	y += 40;
	draw_separator(d, W - PROPERTIES_LIMIT, y, 0x008800);
	draw_separator(d, W - PROPERTIES_LIMIT, y + prop[5]->h + 10, 0x008800);
	x = (W - PROPERTIES_LIMIT * 0.5) - prop[5]->w * 0.5;
	copy_surface_to_surface(prop[5], d->screen, (int[2]){x, y + 5}, d);
	y += prop[5]->h + 90;
	draw_separator(d, W - PROPERTIES_LIMIT, y, 0x008800);
	draw_separator(d, W - PROPERTIES_LIMIT, y + prop[6]->h + 10, 0x008800);
	x = (W - PROPERTIES_LIMIT * 0.5) - prop[6]->w * 0.5;
	copy_surface_to_surface(prop[6], d->screen, (int[2]){x, y + 5}, d);
	y = H * 0.40;
	draw_separator(d, W - PROPERTIES_LIMIT, y, 0x008800);
	draw_separator(d, W - PROPERTIES_LIMIT, y + prop[7]->h + 10, 0x008800);
	x = (W - PROPERTIES_LIMIT * 0.5) - prop[7]->w * 0.5;
	copy_surface_to_surface(prop[7], d->screen, (int[2]){x, y + 5}, d);
	print_assets(d, d->interface.toolbar.assets);
}

static void	print_texture_toolbar(t_data *d, int tex_case)
{
	int			i;
	int			x;
	int			y;
	SDL_Surface	**tex;

	if (!(tex = (tex_case == 3) ? d->posters : d->textures))
		return ;
	y = -1;
	while (++y < H)
		putpixel(d, W - TEXTURE_TOOLBAR, y, 0x008800);
	x = W - TEXTURE_TOOLBAR + MARGIN;
	i = -1;
	y = MARGIN;
	while (++i < ((tex_case == 3) ? d->nb_posters : d->nb_texture))
	{
		if (tex[i]->w != 64 || tex[i]->h != 64)
			d->texture_to_scale = 64;
		copy_surface_to_surface(tex[i], d->screen, (int[2]){x, y}, d);
		x += 64;
		if ((i + 1) % 4 == 0 && (y += 64))
			x = W - TEXTURE_TOOLBAR + MARGIN;
		d->texture_to_scale = -1;
	}
}

/*
**	29 = button height in toolbar->select
**	can get the height using : d->interface.toolbar.select[0]->h
*/

void		print_interface(t_data *d)
{
	int	y;
	int	i;

	if (d->interface.show_menu)
		copy_surface_to_surface(d->interface.menu, d->screen, (int[2]){0, 0},
																		d);
	i = (!d->interface.select) ? 0 : 1;
	copy_surface_to_surface(d->interface.toolbar.select[i], d->screen,
											(int[2]){0, H * 0.5 - 29}, d);
	i = (!d->interface.move) ? 0 : 1;
	copy_surface_to_surface(d->interface.toolbar.move[i], d->screen,
											(int[2]){0, H * 0.5}, d);
	if (d->interface.texture_case_select != -1)
		print_texture_toolbar(d, d->interface.texture_case_select);
	y = 0;
	while (y++ < H)
		putpixel(d, W - PROPERTIES_LIMIT, y, 0x008800);
	print_properties(d, d->interface.toolbar.properties);
	print_assets_toolbar(d, d->interface.toolbar.properties);
	print_interface_values(d, 0, 0);
	draw_ligth_bar(d);
}
