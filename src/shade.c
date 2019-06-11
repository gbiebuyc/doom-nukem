/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 00:57:43 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/11 16:00:34 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

double		getshadefactor(t_data *d, t_projdata *p, double dist)
{
	double factor;

	factor = (p->sector->blinking) ? d->lightblink : p->sector->light;
	if (dist && !p->sector->outdoor)
		factor -= dist / 20;
	return (factor);
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
