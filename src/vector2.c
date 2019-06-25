/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 00:15:33 by nallani           #+#    #+#             */
/*   Updated: 2019/06/25 21:45:20 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

t_vec2f	mul_vec2f(t_vec2f v, double scalar)
{
	return ((t_vec2f){v.x * scalar, v.y * scalar});
}

bool	is_inside_vec2f(t_vec2f p1, t_vec2f p2, t_vec2f point)
{
	point.x *= 100000000;
	point.x = roundf(point.x);
	point.x /= 100000000;
	point.y *= 100000000;
	point.y = roundf(point.y);
	point.y /= 100000000;
	if ((point.x < p1.x && point.x < p2.x) ||
			(point.x > p1.x && point.x > p2.x))
		return (false);
	if ((point.y < p1.y && point.y < p2.y) ||
			(point.y > p1.y && point.y > p2.y))
		return (false);
	return (true);
}

float	get_vec2f_length(t_vec2f v)
{
	return (v.x * v.x + v.y * v.y);
}

double	vec2f_length(t_vec2f v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

double	get_vec2f_angle(t_vec2f v1, t_vec2f v2)
{
	return (atan2(v1.x * v2.y - v1.y * v2.x, v1.x * v2.x + v1.y * v2.y));
}
