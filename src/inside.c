/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 05:45:22 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/29 02:07:05 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Used to detect the current sector at each frame.
*/

bool	inside(t_data *d, int16_t sectnum)
{
	int i, j;
	bool c = 0;

	int npoints = d->sectors[sectnum].numwalls;
	for (i = 0, j = npoints-1; i < npoints; j = i++)
	{
		t_vec2f p0 = d->walls[d->sectors[sectnum].firstwallnum + i].point;
		t_vec2f p1 = d->walls[d->sectors[sectnum].firstwallnum + j].point;
		t_vec2f test = (t_vec2f){d->cam.pos.x, d->cam.pos.z};
		if ( ((p0.y > test.y) != (p1.y > test.y)) &&
				(test.x < (p1.x-p0.x) * (test.y-p0.y) / (p1.y-p0.y) + p0.x) )
			c = !c;
	}
	return (c);
}
