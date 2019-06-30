/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 00:57:43 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/30 20:34:11 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

double		getshadefactor(t_data *d, t_projdata *p, double dist)
{
	double factor;

	factor = (p->sector->blinking) ? d->lightblink : p->sector->light;
	if (dist && !p->sector->outdoor && p->sector->light == 1)
		factor -= dist / 20;
	return (factor);
}

uint32_t	sprite_shade(t_data *d, t_sector *sector, double dist, uint32_t img)
{
	double	factor;

	factor = (sector->blinking) ? d->lightblink : sector->light;
	if (dist && !sector->outdoor && sector->light == 1)
		factor -= dist / 30;
	if (factor <= 0)
		return (0);
	if (factor >= 1)
		return (img);
	return (((int)(((img >> 16) & 0xff) * factor) << 16) |
			((int)(((img >> 8) & 0xff) * factor) << 8) |
			((int)(((img >> 0) & 0xff) * factor) << 0));
}

uint32_t	shade(double factor, uint32_t c)
{
	if (factor <= 0)
		return (0);
	if (factor >= 1)
		return (c);
	return (((int)(((c >> 16) & 0xff) * factor) << 16) |
			((int)(((c >> 8) & 0xff) * factor) << 8) |
			((int)(((c >> 0) & 0xff) * factor) << 0));
}
