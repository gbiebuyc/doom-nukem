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

static void	prompt_asset_option(t_data *d, t_assets_list *lst)
{
	int		x;
	int		y;
	char	*string;

	x = d->interface.toolbar.properties[6]->w;
	y = H - d->interface.toolbar.properties[6]->h;
	d->interface.prompt_asset_option = 1;
	copy_surface_to_surface(d->interface.toolbar.properties[6], d->screen,
														(int[2]){0, y}, d);
	string = ft_itoa_static(lst->num_asset);
	draw_string(d, (t_font){string, x - 40, y + 8, 0x008800, 2});
	d->interface.current_selected_asset = lst;
}

static void	draw_assets(t_data *d, SDL_Surface *a[3][100])
{
	t_assets_list	*lst;
	t_vec2f			p;

	if (!d->interface.assets_list)
		return ;
	lst = d->interface.assets_list->begin;
	while (lst)
	{
		p = worldtoscreen(d, lst->world_pos);
		if (p.x + 16 < W - (d->interface.texture_case_select != -1 ?
							TEXTURE_TOOLBAR : PROPERTIES_LIMIT))
		{
			d->texture_to_scale = 32;
			copy_surface_to_surface(a[0][lst->picnum], d->screen,
									(int[2]){p.x - 16, p.y - 16}, d);
			d->texture_to_scale = -1;
			if (lst->is_highlighted || lst->is_select)
			{
				draw_selection_arround_selected_asset(d, &(t_vec2){p.x - 16,
					p.y - 16}, (lst->is_select) ? 0x00ff00 : 0xffff00);
				(lst->is_select) ? prompt_asset_option(d, lst) : 1;
			}
		}
		lst = lst->next;
	}
}

static void	draw_monster(t_data *d, SDL_Surface *a[3][100])
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
		if (p.x + 16 < W - (d->interface.texture_case_select != -1 ?
							TEXTURE_TOOLBAR : PROPERTIES_LIMIT))
		{
			copy_surface_to_surface(
				a[lst->category][lst->selected_asset], d->screen,
				(int[2]){p.x - 16, p.y - 16}, d);
			if (lst->is_highlighted || lst->is_select)
				draw_selection_arround_selected_asset(d, &(t_vec2){p.x - 16,
					p.y - 16}, (lst->is_select) ? 0x00ff00 : 0xffff00);
		}
		lst = lst->next;
	}
	d->texture_to_scale = -1;
}

void		draw_assets_to_map(t_data *d, SDL_Surface *a[3][100])
{
	t_vec2f	p;

	p = worldtoscreen(d, (t_vec2f){d->player_start.x, d->player_start.z});
	d->texture_to_scale = 32;
	if (p.x + 16 < W - PROPERTIES_LIMIT)
		copy_surface_to_surface(d->interface.toolbar.player_start, d->screen,
										(int[2]){p.x - 16, p.y - 16}, d);
	d->texture_to_scale = -1;
	draw_monster(d, a);
	draw_assets(d, a);
}
