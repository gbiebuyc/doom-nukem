/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_draw_assets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 17:46:34 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/01 17:46:35 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_monster(t_data *d , t_assets *a)
{
	t_monster_list	*lst;
	t_vec2f			p;

	if (!d->interface.monster_list)
		return ;
	lst = d->interface.monster_list->begin;
	d->texture_to_scale = 32;
	while (lst)
	{
		p = worldtoscreen(d, lst->pos);
		if (p.x + 16 < W - PROPERTIES_LIMIT)
			copy_surface_to_surface(
				a[lst->category].assets[lst->selected_asset], d->screen,
				(int[2]){p.x - 16, p.y - 16}, d);
		if (lst->is_highlighted || lst->is_select)
			draw_selection_arround_selected_asset(d, &(t_vec2f){p.x - 16,
				p.y - 16}, (lst->is_select) ? 0x00ff00 : 0xffff00);
		lst = lst->next;
	}
	d->texture_to_scale = -1;
}

void	draw_assets_to_map(t_data *d, t_assets *a)
{
	t_vec2f	p;

	p = worldtoscreen(d, (t_vec2f){d->player_start.x, d->player_start.z});
	if (p.x + 16 < W - PROPERTIES_LIMIT)
		copy_surface_to_surface(d->interface.toolbar.player_start, d->screen,
										(int[2]){p.x - 16, p.y - 16}, d);
	draw_monster(d, a);
	// TODO monsters assets + select assets on the map + delete
}
