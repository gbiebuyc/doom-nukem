/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_m16_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 19:23:42 by nallani           #+#    #+#             */
/*   Updated: 2019/06/23 19:27:46 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

double		line_point_collision(t_vec3f orig, t_vec3f dest, t_vec3f pos)
{
	double t;

	t = -(((pos.x - orig.x) * (dest.x - orig.x)) / pow((dest.x - orig.x), 2));
}
