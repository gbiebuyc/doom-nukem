/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:02:41 by nallani           #+#    #+#             */
/*   Updated: 2019/04/02 17:05:03 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_vec2f		projection(t_vec3f vec3,t_vec3f dir)
{
	t_vec2f	result;
	double	angle;

	angle = get_vec2f_angle((t_vec2f){dir.x, dir.z);}

	return (result);
}
