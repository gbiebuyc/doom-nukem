/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorceilheight.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:41:10 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/21 17:41:10 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
**	Height of the floor/ceil at point.
*/

double	get_floorheight2(t_data *d, int16_t sectnum, t_vec2f p)
{
	t_sector	*sect;
	double		angle;

	if (sectnum < 0)
		exit(ft_printf("bad sectnum\n"));
	sect = &d->sectors[sectnum];
	if (sect->slope == 0)
		return (sect->floorheight);
	angle = d->sectors[sectnum].slope_orientation * M_PI / 180;
	p = (t_vec2f){p.x * cos(angle) - p.y * sin(angle),
			p.x * sin(angle) + p.y * cos(angle)};
	return (sect->floorheight + tan(sect->slope * M_PI / 180) *
			(p.x - d->walls[sect->firstwallnum].point.x));
}

double	get_ceilheight2(t_data *d, int16_t sectnum, t_vec2f p)
{
	t_sector	*sect;
	double		angle;

	if (sectnum < 0)
		exit(ft_printf("bad sectnum\n"));
	sect = &d->sectors[sectnum];
	if (sect->slopeceil == 0)
		return (sect->ceilheight);
	angle = d->sectors[sectnum].slopeceil_orientation * M_PI / 180;
	p = (t_vec2f){p.x * cos(angle) - p.y * sin(angle),
			p.x * sin(angle) + p.y * cos(angle)};
	return (sect->ceilheight + tan(sect->slopeceil * M_PI / 180) *
			(p.x - d->walls[sect->firstwallnum].point.x));
}

/*
**	Height of the floor/ceil under the player.
*/

double	get_floorheight(t_data *d, int16_t sectnum)
{
	return (get_floorheight2(d, sectnum, vec3to2(d->cam.pos)));
}

double	get_ceilheight(t_data *d, int16_t sectnum)
{
	return (get_ceilheight2(d, sectnum, vec3to2(d->cam.pos)));
}

/*
**	Delta height between player and floor/ceil at point.
*/

double	get_floordh(t_data *d, t_sector *sect, t_vec3f v)
{
	return (get_floorheight2(d, sect - d->sectors, vec3to2(v)) -
			d->cam.pos.y);
}
double	get_ceildh(t_data *d, t_sector *sect, t_vec3f v)
{
	return (get_ceilheight2(d, sect - d->sectors, vec3to2(v)) -
			d->cam.pos.y);
}
