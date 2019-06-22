/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floceiheight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 23:49:28 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/22 23:49:28 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_vec2f get_sector_center(t_data *d, t_sector *sect)
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
	double		orientation;

	if (sectnum < 0)
		exit(ft_printf("bad sectnum\n"));
	sect = &d->sectors[sectnum];
	h = is_floor ? sect->floorheight : sect->ceilheight;
	slope = is_floor ? sect->slope : sect->slopeceil;
	if (slope == 0)
		return (h);
	orientation = is_floor ? sect->slope_orientation :
		sect->slopeceil_orientation;
	center = get_sector_center(d, sect);
	p = rotate_point(p, center, (sect->is_animatedslope) ?
			(SDL_GetTicks() / 1000.0) : (orientation * M_PI / 180));
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
