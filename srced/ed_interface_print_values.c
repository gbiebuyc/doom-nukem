/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_interface_print_values.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 18:39:03 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/15 18:39:04 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	print_next_map(t_data *d, int x, int y)
{
	char	string[100];

	x = d->interface.box_nex_map_p.x;
	y = d->interface.box_nex_map_p.y;
	copy_surface_to_surface(d->interface.toolbar.properties[18], d->screen,
														(int[2]){x, y}, d);
	ft_memset(string, 0, 100);
	if (d->sectors[d->selected_sector].is_finish && d->next_map[0])
	{
		ft_strncpy(string, d->next_map, ft_strlen(d->next_map) - 6);
		draw_string(d, (t_font){string, x + 28, y + 3, 0x008800, 2});
	}
	else
		draw_string(d, (t_font){"No next map", x + 28, y + 3,
														0x008800, 2});
}

void	print_interface_values(t_data *d, int x, int y)
{
	char	*string;

	x = d->interface.btn_floor_height_pos.x - 85;
	y = PROPERTIES_POS;
	string = ft_itoa_static(d->selected_sector);
	if (d->selected_sector != -1)
		draw_string(d, (t_font){string, x, y + 6, 0x008800, 2});
	else
		draw_string(d, (t_font){"Default", x, y + 6, 0x008800, 2});
	if (d->selected_wall != -1 || d->hl_wallnum != -1)
	{
		string = ft_itoa_static((d->hl_wallnum != -1) ? d->hl_wallnum
														: d->selected_wall);
		draw_string(d, (t_font){string, x, H - 167, 0x008800, 2});
	}
	else
		draw_string(d, (t_font){"Default", x, H - 167, 0x008800, 2});
	string = ft_itoa_static(d->sectors[d->selected_sector].floorheight * 10);
	draw_string(d, (t_font){string, x,
					d->interface.btn_floor_height_pos.y + 4, 0x008800, 2});
	string = ft_itoa_static(d->sectors[d->selected_sector].ceilheight * 10);
	draw_string(d, (t_font){string, x,
					d->interface.btn_ceil_height_pos.y + 4, 0x008800, 2});
	print_next_map(d, x, y);
}
