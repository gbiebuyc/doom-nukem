/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_event_assets_options.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 16:58:57 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/21 16:58:58 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	link_key_with_door(t_data *d, t_assets_list *a)
{
	int	w;
	int	wall_num;

	wall_num = (d->selected_wall == -1) ? d->hl_wallnum : d->selected_wall;
	if ((d->nb_door <= 0 || wall_num == -1 || !d->walls[wall_num].is_door) &&
		!a->is_key)
		return (ft_printf("There is no door to link the key with.\n"));
	if (a->is_key)
	{
		w = -1;
		while (++w < d->numwalls)
			if (d->walls[w].key_num == a->key_num)
				d->walls[w].key_num = 0;
	}
	else
	{
		d->nb_keys++;
		a->key_num = d->nb_keys;
		w = -1;
		while (++w < d->numwalls)
			if (d->walls[w].door_num == d->walls[wall_num].door_num)
				d->walls[w].key_num = a->key_num;
	}
	a->is_key = !a->is_key;
	return (0);
}

int			is_on_button(t_vec2 btn, int x, int y)
{
	return (x >= btn.x && x < btn.x + 24 && y >= btn.y && y < btn.y + 24);
}

static void	handle_checkbox(t_data *d, int x, int y, t_assets_list *a)
{
	if (is_on_button(d->interface.btn_option_p.cbox_onfloor, x, y))
	{
		a->is_on_floor = true;
		a->is_on_ceil = false;
	}
	else if (is_on_button(d->interface.btn_option_p.cbox_onceil, x, y))
	{
		a->is_on_floor = false;
		a->is_on_ceil = true;
	}
	else if (is_on_button(d->interface.btn_option_p.cbox_isinteractive, x, y))
		a->is_interactive = !a->is_interactive;
	else if (is_on_button(d->interface.btn_option_p.cbox_autopickup, x, y))
		a->is_autopick = !a->is_autopick;
	else if (is_on_button(d->interface.btn_option_p.cbox_collision, x, y))
		a->collision = !a->collision;
	else if (is_on_button(d->interface.btn_option_p.cbox_jetpack, x, y))
		a->is_jetpack = !a->is_jetpack;
	else if (is_on_button(d->interface.btn_option_p.cbox_key, x, y))
		link_key_with_door(d, a);
}

void		event_asset_option_handler(t_data *d, int x, int y,
														t_btn_option_p *p)
{
	t_assets_list	*a;

	a = d->interface.current_selected_asset;
	handle_checkbox(d, x, y, a);
	if (is_on_button(p->btn_restorehp_minus, x, y) && a->stat_mod.heal > 0)
		a->stat_mod.heal -= 5;
	else if (is_on_button(p->btn_restorehp_plus, x, y))
		a->stat_mod.heal += (a->stat_mod.heal < 100) ? 5 : 0;
	else if (is_on_button(p->btn_damaehp_minus, x, y))
		a->stat_mod.damage -= (a->stat_mod.damage > 0) ? 5 : 0;
	else if (is_on_button(p->btn_damaehp_plus, x, y))
		a->stat_mod.damage += (a->stat_mod.damage < 100) ? 5 : 0;
	else if (is_on_button(p->btn_ammo_ballista_minus, x, y))
		a->stat_mod.ballista_ammo -= (a->stat_mod.ballista_ammo > -99) ? 1 : 0;
	else if (is_on_button(p->btn_ammo_ballista_plus, x, y))
		a->stat_mod.ballista_ammo += (a->stat_mod.ballista_ammo < 99) ? 1 : 0;
	else if (is_on_button(p->btn_ammo_blaster_minus, x, y))
		a->stat_mod.blaster_ammo -= (a->stat_mod.blaster_ammo > -99) ? 1 : 0;
	else if (is_on_button(p->btn_ammo_blaster_plus, x, y))
		a->stat_mod.blaster_ammo += (a->stat_mod.blaster_ammo < 99) ? 1 : 0;
	else if (is_on_button(p->btn_ammo_m16_minus, x, y))
		a->stat_mod.m16_ammo -= (a->stat_mod.m16_ammo > -99) ? 1 : 0;
	else if (is_on_button(p->btn_ammo_m16_plus, x, y))
		a->stat_mod.m16_ammo += (a->stat_mod.m16_ammo < 99) ? 1 : 0;
}
