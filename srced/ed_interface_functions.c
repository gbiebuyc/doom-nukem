/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_interface_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 01:07:21 by mikorale          #+#    #+#             */
/*   Updated: 2019/05/15 01:07:21 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_vec2f	grid_lock(t_data *d, t_vec2f p)
{
	if (!d->grid_locking)
		return (p);
	return ((t_vec2f){floor(p.x + 0.5), floor(p.y + 0.5)});
}

int		is_on_select_move_icon(t_data *d, int x, int y)
{
	if (!d->interface.btn_right_pressed)
	{
		if (x >= 0 && x < 29 && y >= H * 0.5 - 29 && y < H * 0.5)
		{
			d->interface.select = 1;
			d->interface.move = 0;
			return (1);
		}
		else if (x >= 0 && x < 29 && y >= H * 0.5 && y < H * 0.5 + 29)
		{
			d->interface.select = 0;
			d->interface.move = 1;
			return (1);
		}
	}
	return (0);
}

int		check_if_mouse_on_menu(t_data *d, int x, int y)
{
	if (d->interface.show_menu)
	{
		if (x >= 6 && x < d->interface.menu->w - 6)
		{
			if (y >= 6 && y < 34)
				return (1);
			else if (y >= 34 && y < 62)
				return (2);
			else if (y >= 62 && y < 90)
				return (3);
		}
	}
	return (0);
}

void	btn_sector_height(t_data *d, int x, int y, t_interface *i)
{
	int endx;
	int	endy;

	endx = i->btn_floor_height_pos.x + 24;
	endy = i->btn_floor_height_pos.y + 24;
	if (y >= i->btn_floor_height_pos.y && y <= endy)
	{
		if (x >= i->btn_floor_height_pos.x && x <= endx)
			floor_height(d, -0.1, d->selected_sector);
		else if (x >= i->btn_floor_height_pos.x + 32 && x <= endx + 32)
			floor_height(d, 0.1, d->selected_sector);
	}
	endy = i->btn_ceil_height_pos.y + 24;
	if (y >= i->btn_ceil_height_pos.y && y <= endy)
	{
		if (x >= i->btn_ceil_height_pos.x && x <= endx)
			ceil_height(d, -0.1, d->selected_sector);
		else if (x >= i->btn_ceil_height_pos.x + 32 && x <= endx + 32)
			ceil_height(d, 0.1, d->selected_sector);
	}
}

void	is_on_checkbox(t_data *d, int x, int y, SDL_Event *e)
{
	t_vec2	*xy;

	xy = (t_vec2[4]){d->interface.cbox_door_p, d->interface.cbox_skybox_p,
					d->interface.cbox_end_p, d->interface.box_nex_map_p};
	if (x > xy[0].x && x <= xy[0].x + 24 && y > xy[0].y && y <= xy[0].y + 24)
		toggle_isdoor(d, 0);
	if (x > xy[1].x && x <= xy[1].x + 24 && y > xy[1].y && y <= xy[1].y + 24)
		d->sectors[d->selected_sector].outdoor =
			!d->sectors[d->selected_sector].outdoor;
	if (x > xy[2].x && x <= xy[2].x + 24 && y > xy[2].y && y <= xy[2].y + 24 &&
		d->selected_sector != -1)
	{
		if (d->selected_sector != d->startsectnum)
			d->sectors[d->selected_sector].is_finish =
				!d->sectors[d->selected_sector].is_finish;
		else
			ft_printf("Can't set the end and start on the same sector.\n");
	}
	if (x > xy[3].x && x <= xy[3].x + 24 && y > xy[3].y && y <= xy[3].y + 24)
		get_next_level(d, e);
}
