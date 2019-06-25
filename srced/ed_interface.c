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

static void	print_assets(t_data *d, SDL_Surface *a[3][100])
{
	int	m;
	int	j;
	int	x;
	int	y;

	m = -1;
	while (++m < NB_CATEGORY - 1 && (j = -1) < 0)
	{
		y = d->interface.category_pos[m].y;
		x = W - PROPERTIES_LIMIT - 30;
		while (++j < d->interface.nb_asset[m])
		{
			cpy_scale_surf(a[m][j], (int[2]){x += 38, y}, 32, d);
			if (j != 0 && ((j + 1) % (NB_ASSET_LINE)) == 0 && (y += 36))
				x = W - PROPERTIES_LIMIT - 30;
		}
	}
	x = d->interface.category_pos[2].x;
	y = d->interface.category_pos[2].y;
	cpy_scale_surf(d->interface.toolbar.player_start, (int[2]){x, y}, 32, d);
}

static void	print_assets_toolbar(t_data *d, SDL_Surface **prop)
{
	int	x;
	int	y;

	x = (W - PROPERTIES_LIMIT * 0.5) - prop[4]->w * 0.5;
	y = 5;
	copy_surface_to_surface(prop[4], d->screen, (int[2]){x, y}, d);
	y += prop[4]->h + 5;
	d->interface.category_pos[0] = (t_vec2){W - PROPERTIES_LIMIT + 7, y + 4};
	draw_separator(d, W - PROPERTIES_LIMIT, y, 0x008800);
	y += 364;
	d->interface.category_pos[1] = (t_vec2){W - PROPERTIES_LIMIT + 7,
											y + prop[5]->h + 13};
	draw_separator(d, W - PROPERTIES_LIMIT, y, 0x008800);
	draw_separator(d, W - PROPERTIES_LIMIT, y + prop[5]->h + 10, 0x008800);
	x = (W - PROPERTIES_LIMIT * 0.5) - prop[5]->w * 0.5;
	copy_surface_to_surface(prop[5], d->screen, (int[2]){x, y + 5}, d);
	y += prop[5]->h + 90;
	x = (W - PROPERTIES_LIMIT * 0.5) - prop[6]->w * 0.5;
	y = PROPERTIES_POS - prop[7]->h - 15;
	draw_separator(d, W - PROPERTIES_LIMIT, y, 0x008800);
	x = W - PROPERTIES_LIMIT + 8;
	copy_surface_to_surface(prop[7], d->screen, (int[2]){x, y + 5}, d);
	d->interface.category_pos[2] = (t_vec2){x + prop[7]->w + 10, y + 5};
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
		cpy_scale_surf(tex[i], (int[2]){x, y}, 64, d);
		x += 64;
		if ((i + 1) % 4 == 0 && (y += 64))
			x = W - TEXTURE_TOOLBAR + MARGIN;
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
	print_properties(d, d->interface.toolbar.properties, 0, PROPERTIES_POS);
	print_assets_toolbar(d, d->interface.toolbar.properties);
	print_interface_values(d, d->interface.btn_floor_height_pos.x - 85,
												PROPERTIES_POS, NULL);
	draw_ligth_bar(d);
}
