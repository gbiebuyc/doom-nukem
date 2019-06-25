/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:43:51 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/25 21:44:50 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

double	vec3f_length(t_vec3f v)
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
