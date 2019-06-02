/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_detect_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 17:38:31 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/02 19:20:49 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

double	fclamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

void	detect_wall(t_data *d, int x, int y)
{
	int16_t	s;
	int16_t	w1;
	int16_t	w2;
	int16_t	last;

	s = -1;
	while (++s < d->numsectors)
	{
		last = d->sectors[s].firstwallnum + d->sectors[s].numwalls;
		w1 = last - 1;
		w2 = d->sectors[s].firstwallnum;
		while (w2 < last)
		{
			t_vec2f a = worldtoscreen(d, d->walls[w1].point);
			t_vec2f b = worldtoscreen(d, d->walls[w2].point);
			t_vec2f p = (t_vec2f){x, y};
			t_vec2f a_to_p = {p.x - a.x, p.y - a.y};
			t_vec2f	a_to_b = {b.x - a.x, b.y - a.y};
			double	atb2 = a_to_b.x * a_to_b.x + a_to_b.y * a_to_b.y;
			double	atp_dot_atb = a_to_p.x * a_to_b.x + a_to_p.y * a_to_b.y;
			double	t = atp_dot_atb / atb2;
			t = fclamp(t, 0, 1);
			t_vec2f	closest = {a.x + t * a_to_b.x, a.y + t * a_to_b.y};
			double	dx = p.x - closest.x;
			double	dy = p.y - closest.y;
			double	dist = vec2f_length((t_vec2f){dx, dy});
			if (dist < 15)
				return ((void)(d->highlighted_wall = &d->walls[w1]));
			w1 = w2++;
		}
	}
	d->highlighted_wall = NULL;
}
