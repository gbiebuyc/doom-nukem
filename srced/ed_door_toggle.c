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
	t_sector	*sect;
	int16_t		wallnum;
	int16_t		nextwallnum;

	sect = &d->sectors[in_which_sector_is_this_wall(d, w)];
	wallnum = w - d->walls;
	nextwallnum = ((wallnum - sect->firstwallnum + 1) %
			sect->numwalls) + sect->firstwallnum;
	return (&d->walls[nextwallnum]);
}

/*
**	get the portal from the neighbor sector and set it as a door too.
*/

void	find_opposite_portal(t_data *d, t_sector *neighborsect, int16_t *last,
							t_wall *nextwall)
{
	int		i;
	int		j;

	i = *last - 1;
	j = neighborsect->firstwallnum;
	while (j < *last)
	{
		if (d->walls[i].neighborsect != -1 &&
			same_pos(&d->walls[i], nextwall) &&
			same_pos(&d->walls[j], d->selectedwall))
		{
			d->walls[i].is_door = d->selectedwall->is_door;
			break ;
		}
		i = j++;
	}
}

void	toggle_isdoor(t_data *d)
{
	t_sector	*neighborsect;
	t_wall		*nextwall;
	int16_t		last;

	if (d->selected_wall != -1 || d->hl_wallnum != -1)
	{
		d->selectedwall = d->walls +
				((d->selected_wall != -1) ? d->selected_wall : d->hl_wallnum);
		if (d->selectedwall->neighborsect == -1)
		{
			ft_printf("Only portals can be doors !\n");
			return ;
		}
		d->selectedwall->is_door = !d->selectedwall->is_door;
		neighborsect = d->sectors + d->selectedwall->neighborsect;
		nextwall = get_adjacent_wall(d, d->selectedwall);
		last = neighborsect->firstwallnum + neighborsect->numwalls;
		find_opposite_portal(d, neighborsect, &last, nextwall);
		printf("is_door: %d\n", d->selectedwall->is_door);
	}
	d->selectedwall = NULL;
}
