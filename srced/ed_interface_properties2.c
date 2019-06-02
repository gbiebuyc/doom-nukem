/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_interface_properties2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 07:42:18 by mikorale          #+#    #+#             */
/*   Updated: 2019/05/20 07:42:19 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		draw_separator(t_data *d, int x, int y, int color)
{
	while (x < W)
	{
		putpixel(d, x, y, color);
		x++;
	}
}

static void	empty_case(t_data *d, int n, t_interface *i)
{
	int	x;
	int	y;

	while (--n >= 0)
	{
		y = -1;
		while (++y < 64)
		{
			x = -1;
			while (++x < 64)
				putpixel(d, x + i->tex_select[n].x + 1,
						y + i->tex_select[n].y + 1, 0x000000);
		}
	}
}

void		fill_texture_selection(t_data *d, t_interface *i)
{
	int tex_n;

	if (d->numwalls <= 0 && d->numsectors <= 0)
		return ;
	d->texture_to_scale = 64;
	if (d->selected_wall != -1)
	{
		tex_n = d->walls[d->selected_wall].middlepicnum;
		copy_surface_to_surface(d->textures[tex_n], d->screen,
				(int[2]){i->tex_select[2].x + 1, i->tex_select[2].y + 1}, d);
	}
	else
		empty_case(d, 1, i);
	tex_n = d->sectors[d->selected_sector].ceilpicnum;
	if (d->selected_sector != -1)
	{
		copy_surface_to_surface(d->textures[tex_n], d->screen,
				(int[2]){i->tex_select[1].x + 1, i->tex_select[1].y + 1}, d);
		tex_n = d->sectors[d->selected_sector].floorpicnum;
		copy_surface_to_surface(d->textures[tex_n], d->screen,
				(int[2]){i->tex_select[0].x + 1, i->tex_select[0].y + 1}, d);
	}
	else
		empty_case(d, 2, i);
	d->texture_to_scale = -1;
}

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
