/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 18:21:39 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/26 18:43:10 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_vec2f	intersect(t_vec2f p0, t_vec2f p1, t_vec2f p2, t_vec2f p3)
{
	double a1 = p1.y - p0.y;
	double b1 = p0.x - p1.x;
	double c1 = a1 * p0.x + b1 * p0.y;
	double a2 = p3.y - p2.y;
	double b2 = p2.x - p3.x;
	double c2 = a2 * p2.x + b2 * p2.y;
	double denominator = a1 * b2 - a2 * b1;
	if (denominator == 0)
		return ((t_vec2f){-1, -1});
	return ((t_vec2f){(b2 * c1 - b1 * c2) / denominator,
			(a1 * c2 - a2 * c1) / denominator});
}

/*
** clip_wall
** returns true if clipped successfully
** returns false if wall outside field of view
*/

bool	clip_wall(t_vec3f *p0, t_vec3f p1)
{
	// clip du cote de l'x a l'origine
	double x_intercept = lerp(norm(0, p0->z, p1.z), p0->x, p1.x);
	double side = (x_intercept < 0) ? -1 : 1;
	t_vec2f near = {((side * WIDTH / 2.0) / WIDTH) * 1.0, 1};
	t_vec2f far = {((side * WIDTH / 2.0) / WIDTH) * 10.0, 10};
	t_vec2f inter = intersect(vec3to2(*p0), vec3to2(p1), near, far);
	if (inter.y <= 0)
		return (false);
	if (((p0->x - p1.x) < 0) != ((inter.x - p1.x) < 0))
		return (false);
	p0->x = inter.x;
	p0->z = inter.y;
	return (true);
}
