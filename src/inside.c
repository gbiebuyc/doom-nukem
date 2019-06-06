/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 05:45:22 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/05 21:01:35 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Used to detect the current sector at each frame.
*/

bool	inside(t_data *d, int16_t sectnum, t_vec2f pos)
{
	int i, j;
	bool c = 0;

	int npoints = d->sectors[sectnum].numwalls;
	for (i = 0, j = npoints-1; i < npoints; j = i++)
	{
		t_vec2f p0 = d->walls[d->sectors[sectnum].firstwallnum + i].point;
		t_vec2f p1 = d->walls[d->sectors[sectnum].firstwallnum + j].point;
		if ( ((p0.y > pos.y) != (p1.y > pos.y)) &&
				(pos.x < (p1.x-p0.x) * (pos.y-p0.y) / (p1.y-p0.y) + p0.x) )
			c = !c;
	}
	return (c);
}

#define DIST_COLL_PROJ_CEIL_FLOOR 0.1

int16_t	update_cursect(int16_t sect_to_scan, t_data *d, int depth,
int16_t old_sect, t_vec3f pos)
{
	short	i;
	short	j;
	short	ret_value;

	if (inside(d, sect_to_scan, (t_vec2f){pos.x, pos.z}) && pos.y < d->sectors[sect_to_scan].ceilheight + DIST_COLL_PROJ_CEIL_FLOOR && pos.y > d->sectors[sect_to_scan].floorheight + DIST_COLL_PROJ_CEIL_FLOOR)
	{
		return (sect_to_scan);
	}
	if (!depth)
		return (-1);
	i = d->sectors[sect_to_scan].firstwallnum;
	j = d->sectors[sect_to_scan].firstwallnum + d->sectors[sect_to_scan].numwalls;
//	printf("cur sec: %d, numwalls :%d\n", sect_to_scan, d->sectors[sect_to_scan].numwalls);
	while (i < j)
	{
		if (d->walls[i].neighborsect != -1 && d->walls[i].neighborsect != old_sect)
			if ((ret_value = update_cursect(d->walls[i].neighborsect, d, depth - 1, sect_to_scan, pos)) != -1)
			{
//				printf("%d\n", ret_value);
				return (ret_value);
				}
		i++;
	}
	return (-1);
}
