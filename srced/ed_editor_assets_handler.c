/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_editor_assets_handler.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 15:48:23 by mikorale          #+#    #+#             */
/*   Updated: 2019/05/27 15:48:30 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_selection_arround_selected_asset(t_data *d)
{
	int		x;
	int		y;
	t_vec2f	v;

	x = d->temp.x;
	y = d->temp.y;
	v.x = d->interface.selected_asset_position.x;
	v.y = d->interface.selected_asset_position.y;
	x = -1;
	while (++x < 32)
		putpixel(d, x + v.x, v.y, 0x00ff00);
	x = -1;
	while (++x < 32)
		putpixel(d, x + v.x, v.y + 32, 0x00ff00);
	y = -1;
	while (++y < 32)
		putpixel(d, v.x, y + v.y, 0x00ff00);
	y = -1;
	while (++y < 32)
		putpixel(d, v.x + 32, y + v.y, 0x00ff00);
}

void	get_selected_asset(t_data *d)
{
	int		x;
	int		y;

	x = d->temp.x;
	y = d->temp.y;
	if (x + 1 + y * 7 > d->interface.nb_asset[d->interface.category])
		return ;
	d->interface.selected_asset = x + y * 7;
	d->interface.select = 0;
	x = x * 38 + d->interface.category_pos[d->interface.category].x;
	y = y * 36 + d->interface.category_pos[d->interface.category].y;
	d->interface.selected_asset_position = (t_vec2f){x, y};
	d->interface.selected_asset_cat = d->interface.category;
}

/*
**	4 category (0 to 3)
*/

void	add_asset_to_map(t_data *d, int x, int y)
{
	//t_assets *a;
	int			sectornum;
	float		mid;
	t_sector 	*s;
	t_vec2f		xy;

	sectornum = find_sect_under_cursor(d);
	s = &d->sectors[sectornum];
	xy = screentoworld(d, (t_vec2f){x, y});
	// TODO upgrade wall selection then denied playerstart position
	// if to close from a wall
	if (d->interface.selected_asset_cat == 3 && sectornum >= 0)
	{
		mid = (fabs(s->ceilheight) - fabs(s->floorheight)) * 0.5;
		//printf("%f %f\n", xy.x, xy.y); // TODO Bug depending on player position, probably doom pb not editor
		d->player_start = (t_vec3f){xy.x, s->floorheight + mid, xy.y};
		ft_printf("starting point done\n");
		d->interface.selected_asset_cat = -1;
		d->interface.selected_asset = -1;
		d->interface.select = 1;
	}
	else
		ft_printf("The player starting point must be place inside a sector\n");
//	a = &d->interface.toolbar.assets[d->interface.selected_asset_cat];
//	copy_surface_to_surface(a->assets_icon[d->interface.selected_asset],
//							d->screen, (int[2]){x, y}, d);
}