/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floceiheight2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 23:48:01 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/22 23:48:01 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
**	Height of the floor/ceil under the player.
*/

double	get_floorheight_player(t_data *d, int16_t sectnum)
{
	return (get_floorheight_point(d, sectnum, vec3to2(d->cam.pos)));
}

double	get_ceilheight_player(t_data *d, int16_t sectnum)
{
	return (get_ceilheight_point(d, sectnum, vec3to2(d->cam.pos)));
}

/*
**	Delta height between player and floor/ceil at point.
*/

double	get_floordh(t_data *d, t_sector *sect, t_vec3f v)
{
	return (get_floorheight_point(d, sect - d->sectors, vec3to2(v)) -
			d->cam.pos.y);
}
double	get_ceildh(t_data *d, t_sector *sect, t_vec3f v)
{
	return (get_ceilheight_point(d, sect - d->sectors, vec3to2(v)) -
			d->cam.pos.y);
}
