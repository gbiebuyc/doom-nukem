/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_neighborsects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:46:43 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/07/04 14:21:13 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	same_pos(t_vec2f v1, t_vec2f v2)
{
	return (v1.x == v2.x && v1.y == v2.y);
}

int		find_nei(t_data *d, t_vec2f v0, t_vec2f v1, int sect)
{
	int	s;
	int	w0;
	int	w1;

	s = -1;
	while (++s < d->numsectors)
	{
		w0 = d->sectors[s].firstwallnum + d->sectors[s].numwalls - 1;
		w1 = d->sectors[s].firstwallnum;
		while (w1 < (d->sectors[s].firstwallnum + d->sectors[s].numwalls))
		{
			if (same_pos(d->walls[w0].point, v1) &&
					same_pos(d->walls[w1].point, v0) && (s != sect))
				return (s);
			w0 = w1++;
		}
	}
	return (-1);
}

void	fix_neighborsects(t_data *d)
{
	int	s;
	int	w0;
	int	w1;

	s = -1;
	while (++s < d->numsectors)
	{
		w0 = d->sectors[s].firstwallnum + d->sectors[s].numwalls - 1;
		w1 = d->sectors[s].firstwallnum;
		while (w1 < (d->sectors[s].firstwallnum + d->sectors[s].numwalls))
		{
			d->walls[w0].neighborsect = find_nei(d, d->walls[w0].point,
					d->walls[w1].point, s);
			w0 = w1++;
		}
	}
}
