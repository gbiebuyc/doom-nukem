/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 00:15:33 by nallani           #+#    #+#             */
/*   Updated: 2019/05/22 21:40:32 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

t_vec2f	mul_vec2f(t_vec2f v, double scalar)
{
	return ((t_vec2f){v.x * scalar, v.y * scalar});
}

bool	is_inside_vec2f(t_vec2f p1, t_vec2f p2, t_vec2f point) // unused and to be deleted
{
	point.x *= 100000000;
	point.x = roundf(point.x);
	point.x /= 100000000;
	point.y *= 100000000;
	point.y = roundf(point.y);
	point.y /= 100000000;
	if ((point.x < p1.x && point.x < p2.x) || (point.x > p1.x && point.x > p2.x))
		return (false);
	if ((point.y < p1.y && point.y < p2.y) || (point.y > p1.y && point.y > p2.y))
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

double vec3f_length(t_vec3f v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3f	add_vec3f(t_vec3f a, t_vec3f b)
{
	return ((t_vec3f){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3f	vec2to3(t_vec2f v)
{
	return ((t_vec3f){v.x, 0, v.y});
}

t_vec2f	vec3to2(t_vec3f v)
{
	return ((t_vec2f){v.x, v.z});
}
