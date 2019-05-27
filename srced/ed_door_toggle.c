/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_toggle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 15:41:42 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/27 17:01:44 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_wall	*get_adjacent_wall(t_data *d, t_wall *w)
{
	t_sector *sect = &d->sectors[in_which_sector_is_this_wall(d, w)];
	int16_t wallnum = w - d->walls;
	int16_t nextwallnum = ((wallnum - sect->firstwallnum + 1) %
			sect->numwalls) + sect->firstwallnum;
	return (&d->walls[nextwallnum]);
}

void	toggle_isdoor(t_data *d)
{
	if (d->selected_wall == -1)
	{
		ft_printf("No wall selected\n");
		return ;
	}
	d->selectedwall = d->walls + d->selected_wall;
	if (d->selectedwall->neighborsect == -1)
	{
		ft_printf("Only portals can be doors !\n");
		return ;
	}
	d->selectedwall->is_door = !d->selectedwall->is_door;
	t_sector *nei = d->sectors + d->selectedwall->neighborsect;
	t_wall *nextwall = get_adjacent_wall(d, d->selectedwall);
	int16_t last = nei->firstwallnum + nei->numwalls;
	// find opposite portal and change is_door
	for (int i = last - 1, j = nei->firstwallnum; j < last; i = j++)
	{
		if (d->walls[i].neighborsect == -1)
			continue ;
		if (same_pos(&d->walls[i], nextwall) &&
				same_pos(&d->walls[j], d->selectedwall))
		{
			d->walls[i].is_door = d->selectedwall->is_door;
			break ;
		}
	}
	printf("is_door: %d\n", d->selectedwall->is_door);
}
