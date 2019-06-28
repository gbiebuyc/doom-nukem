/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floceiheight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 23:49:28 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/25 23:14:36 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_vec2f	get_sector_center(t_data *d, t_sector *sect)
{
	int		i;
	t_vec2f	center;

	center = (t_vec2f){0, 0};
	i = -1;
	while (++i < sect->numwalls)
		center = add_vec2f(center, d->walls[sect->firstwallnum + i].point);
	center = mul_vec2f(center, 1.0 / sect->numwalls);
	return (center);
}

t_vec2f	rotate_point(t_vec2f p, t_vec2f center, double angle)
{
	p = sub_vec2f(p, center);
	p = (t_vec2f){p.x * cos(angle) - p.y * sin(angle),
			p.x * sin(angle) + p.y * cos(angle)};
	return (add_vec2f(p, center));
}

double	get_floceiheight(t_data *d, int16_t sectnum, t_vec2f p, bool is_floor)
{
	t_sector	*sect;
	t_vec2f		center;
	double		h;
	double		slope;

	if (sectnum < 0)
		exit(ft_printf("bad sectnum\n"));
	sect = &d->sectors[sectnum];
	h = (is_floor ? sect->floorheight : sect->ceilheight) + ((is_floor &&
				sect->is_elevator) ? sin(SDL_GetTicks() / 1000.0) * 0.5 : 0);
	slope = is_floor ? sect->slope : sect->slopeceil;
	if (slope == 0)
		return (h);
	center = get_sector_center(d, sect);
	p = rotate_point(p, center, ((is_floor ? sect->slope_orientation :
			sect->slopeceil_orientation) * M_PI / 180) + (((is_floor &&
			sect->is_animatedslope) || (!is_floor &&
			sect->is_animatedslopeceil)) ? (SDL_GetTicks() / 1000.0) : 0));
	return (h + tan(slope * M_PI / 180) * (p.x - center.x));
}

/*
**	Height of the floor/ceil at point.
*/

double	get_floorheight_point(t_data *d, int16_t sectnum, t_vec2f p)
{
	return (get_floceiheight(d, sectnum, p, true));
}

double	get_ceilheight_point(t_data *d, int16_t sectnum, t_vec2f p)
{
	return (get_floceiheight(d, sectnum, p, false));
}
