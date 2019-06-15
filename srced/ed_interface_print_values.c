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

void	print_interface_values(t_data *d)
{
	char	*string;

	string = ft_itoa_static(d->selected_sector);
	if (d->selected_sector != -1)
		draw_string(d, (t_font){string, W - 80, H / 2 + 6, 0x008800, 2});
	if (d->selected_wall != -1 || d->hl_wallnum != -1)
	{
		string = ft_itoa_static((d->hl_wallnum != -1) ? d->hl_wallnum
														: d->selected_wall);
		draw_string(d, (t_font){string, W - 80, H - 179, 0x008800, 2});	
	}
	string = ft_itoa_static(d->sectors[d->selected_sector].floorheight * 10);
	draw_string(d, (t_font){string, d->interface.btn_floor_height_pos.x - 75,
					d->interface.btn_floor_height_pos.y + 4, 0x008800, 2});
	string = ft_itoa_static(d->sectors[d->selected_sector].ceilheight * 10);
	draw_string(d, (t_font){string, d->interface.btn_ceil_height_pos.x - 75,
					d->interface.btn_ceil_height_pos.y + 4, 0x008800, 2});
}
