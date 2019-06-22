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

static void	empty_case(t_data *d, t_interface *i)
{
	int	x;
	int	y;

	x = i->tex_select[2].x + 1;
	y = i->tex_select[2].y + 1;
	if (d->selected_wall == -1 && d->hl_wallnum == -1)
		copy_surface_to_surface(d->textures[d->default_wall_texture],
								d->screen, (int[2]){x, y}, d);
	if (d->selected_sector == -1)
	{
		x = i->tex_select[1].x + 1;
		y = i->tex_select[1].y + 1;
		copy_surface_to_surface(d->textures[d->default_ceil_texture],
								d->screen, (int[2]){x, y}, d);
		x = i->tex_select[0].x + 1;
		y = i->tex_select[0].y + 1;
		copy_surface_to_surface(d->textures[d->default_floor_texture],
								d->screen, (int[2]){x, y + 1}, d);
	}
}

void		fill_texture_selection(t_data *d, t_interface *i, int wallnum,
																int tex_n)
{
	d->texture_to_scale = 64;
	if (d->selected_wall != -1 || d->hl_wall)
	{
		tex_n = d->walls[wallnum].middlepicnum;
		copy_surface_to_surface(d->textures[tex_n], d->screen,
				(int[2]){i->tex_select[2].x + 1, i->tex_select[2].y + 1}, d);
		tex_n = d->walls[wallnum].posterpicnum;
		if (tex_n != -1)
			copy_surface_to_surface(d->posters[tex_n], d->screen,
				(int[2]){i->tex_select[3].x + 1, i->tex_select[3].y + 1}, d);
	}
	else
		empty_case(d, i);
	if (d->selected_sector != -1)
	{
		tex_n = d->sectors[d->selected_sector].ceilpicnum;
		copy_surface_to_surface(d->textures[tex_n], d->screen,
				(int[2]){i->tex_select[1].x + 1, i->tex_select[1].y + 1}, d);
		tex_n = d->sectors[d->selected_sector].floorpicnum;
		copy_surface_to_surface(d->textures[tex_n], d->screen,
				(int[2]){i->tex_select[0].x + 1, i->tex_select[0].y + 1}, d);
	}
	else
		empty_case(d, i);
	d->texture_to_scale = -1;
}

void		show_preview(t_data *d, SDL_Surface *a[3][100])
{
	int	n;
	int	x;
	int	y;

	n = d->mouse.x + d->mouse.y * NB_ASSET_LINE;
	if (d->interface.category < NB_CATEGORY - 1)
	{
		x = d->interface.mouse_pos.x + 10;
		y = d->interface.mouse_pos.y + 10;
		if (x + a[d->interface.category][n]->w >= W)
			x = x - (a[d->interface.category][n]->w - (W - x));
		copy_surface_to_surface(a[d->interface.category][n], d->screen,
															(int[2]){x, y}, d);
	}
}

void		draw_ligth_bar(t_data *d)
{
	int	x;
	int	y;
	int	limit;
	int	px;
	int	py;

	px = d->interface.cbox_skybox_p.x;
	py = d->interface.tex_select[1].y + 80;
	y = -1;
	while (++y <= 17 && (x = -1))
	{
		putpixel(d, px, py + y, 0x008800);
		while ((y == 0 || y == 17) && ++x < 101)
			putpixel(d, px + x, py + y, 0x008800);
	}
	y = -1;
	while (++y < 17)
		putpixel(d, px + 101, py + y, 0x008800);
	if (d->selected_sector == -1)
		return ;
	limit = d->sectors[d->selected_sector].light * 100;
	y = -1;
	while (++y < 16 && (x = -1))
		while (++x < limit)
			putpixel(d, x + px + 1, y + py + 1, 0xcccc00);
}
