/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 00:15:33 by nallani           #+#    #+#             */
/*   Updated: 2019/03/26 00:15:56 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_vec2f	mul_vec2f(t_vec2f v, double scalar)
{
	return ((t_vec2f){v.x * scalar, v.y * scalar});
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
