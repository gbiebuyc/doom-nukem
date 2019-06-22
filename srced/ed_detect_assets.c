/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_detect_assets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:38:10 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/08 15:38:11 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
**	browse assets_monsters from the last one to the first one
**	to draw the selection around the latest asset that was print on the screen
*/

void	detect_monsters(t_data *d, int x, int y)
{
	t_monster_list	*lst;
	t_vec2f			p;
	int				found;

	if (!d->interface.monster_list)
		return ;
	lst = d->interface.monster_list;
	found = 0;
	while (lst)
	{
		p = worldtoscreen(d, lst->pos);
		lst->is_highlighted = 0;
		if (!found &&
			x > p.x - 16 && x < p.x + 16 && y > p.y - 16 && y < p.y + 16)
		{
			lst->is_highlighted = 1;
			found = 1;
		}
		lst = lst->prev;
	}
}

void	detect_assets(t_data *d, int x, int y)
{
	t_assets_list	*lst;
	t_vec2f			p;
	int				found;

	detect_monsters(d, x, y);
	if (!d->interface.assets_list)
		return ;
	lst = d->interface.assets_list;
	found = 0;
	while (lst)
	{
		p = worldtoscreen(d, lst->world_pos);
		lst->is_highlighted = 0;
		if (!found &&
			x > p.x - 16 && x < p.x + 16 && y > p.y - 16 && y < p.y + 16)
		{
			lst->is_highlighted = 1;
			found = 1;
		}
		lst = lst->prev;
	}
}
