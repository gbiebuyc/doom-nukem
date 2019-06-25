/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 18:21:39 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/25 22:35:25 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_vec2f	intersect(t_vec2f p0, t_vec2f p1, t_vec2f p2, t_vec2f p3)
{
	double	a[2];
	double	b[2];
	double	c[2];
	double	denominator;

	a[0] = p1.y - p0.y;
	b[0] = p0.x - p1.x;
	c[0] = a[0] * p0.x + b[0] * p0.y;
	a[1] = p3.y - p2.y;
	b[1] = p2.x - p3.x;
	c[1] = a[1] * p2.x + b[1] * p2.y;
	denominator = a[0] * b[1] - a[1] * b[0];
	if (denominator == 0)
		return ((t_vec2f){-1, -1});
	return ((t_vec2f){(b[1] * c[0] - b[0] * c[1]) / denominator,
			(a[0] * c[1] - a[1] * c[0]) / denominator});
}

/*
** clip_wall
** returns true if clipped successfully
** returns false if wall outside field of view
*/

bool	clip_wall(double *x1, double *z1, double x2, double z2)
{
	t_vec2f	p0;
	t_vec2f p1;
	t_vec2f inter;
	double	side;

	p0 = (t_vec2f){*x1, *z1};
	p1 = (t_vec2f){x2, z2};
	side = (lerp(norm(0, p0.y, p1.y), p0.x, p1.x) < 0) ? -1 : 1;
	inter = intersect(p0, p1, (t_vec2f){((side * WIDTH / 2.0) / WIDTH) *
			1.0, 1}, (t_vec2f){((side * WIDTH / 2.0) / WIDTH) * 10.0, 10});
	if (inter.y <= 0)
		return (false);
	if (((p0.x - p1.x) < 0) != ((inter.x - p1.x) < 0))
		return (false);
	*x1 = inter.x;
	*z1 = inter.y;
	return (true);
}
