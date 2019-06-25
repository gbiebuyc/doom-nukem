/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:43:10 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/25 21:43:12 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

t_vec2f	sub_vec2f(t_vec2f v1, t_vec2f v2)
{
	return ((t_vec2f){v1.x - v2.x, v1.y - v2.y});
}

t_vec2f	add_vec2f(t_vec2f v1, t_vec2f v2)
{
	return ((t_vec2f){v1.x + v2.x, v1.y + v2.y});
}

void	actualize_dir(double diff, t_vec2f *dir)
{
	double	x;
	double	y;

	x = dir->x;
	y = dir->y;
	dir->x = x * cos(diff) - y * sin(diff);
	dir->y = x * sin(diff) + y * cos(diff);
}

t_vec3f	sub_vec3f(t_vec3f v1, t_vec3f v2)
{
	return ((t_vec3f){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vec3f	mul_vec3f(t_vec3f v1, double scalar)
{
	return ((t_vec3f){v1.x * scalar, v1.y * scalar, v1.z * scalar});
}
