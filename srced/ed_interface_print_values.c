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

static void	printdata(t_data *d, char *s, int x, int y)
{
	draw_string(d, (t_font){s, x, y, 0x008800, 2});
}

static void	print_asset_values(t_data *d, t_assets_list *a, t_btn_option_p *p,
																t_vec2 **v)
{
	int		x;
	int		i;

	copy_surface_to_surface(d->interface.toolbar.properties[14], d->screen,
		(a->is_on_floor) ? (int[2]){v[0]->x, v[0]->y - 1} :
							(int[2]){v[1]->x, v[1]->y - 1}, d);
	x = p->btn_restorehp_minus.x - 50;
	printdata(d, ft_itoa_static(a->stat_mod.heal), x, v[2]->y + 5);
	printdata(d, ft_itoa_static(a->stat_mod.damage), x, v[3]->y + 5);
	printdata(d, ft_itoa_static(a->stat_mod.ballista_ammo), x, v[4]->y + 5);
	printdata(d, ft_itoa_static(a->stat_mod.blaster_ammo), x, v[5]->y + 5);
	printdata(d, ft_itoa_static(a->stat_mod.m16_ammo), x, v[6]->y + 5);
	i = 6;
	while (++i < 12)
		if ((i == 7 && a->is_interactive) || (i == 8 && a->is_autopick) ||
			(i == 9 && a->collision) || (i == 10 && a->is_jetpack) ||
			(i == 11 && a->is_key))
			copy_surface_to_surface(d->interface.toolbar.properties[14],
						d->screen, (int[2]){v[i]->x, v[i]->y - 1}, d);
}

void		print_next_map(t_data *d, int x, int y)
{
	char			string[100];
	t_btn_option_p	*p;

	p = &d->interface.btn_option_p;
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
	if (d->interface.current_selected_asset)
		print_asset_values(d,
		d->interface.current_selected_asset, &d->interface.btn_option_p,
		(t_vec2*[]){&p->cbox_onfloor, &p->cbox_onceil, &p->btn_restorehp_minus,
		&p->btn_damaehp_minus, &p->btn_ammo_ballista_minus,
		&p->btn_ammo_blaster_minus, &p->btn_ammo_m16_minus,
		&p->cbox_isinteractive, &p->cbox_autopickup, &p->cbox_collision,
		&p->cbox_jetpack, &p->cbox_key});
}

void		print_interface_values(t_data *d, int x, int y)
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
