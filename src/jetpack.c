/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jetpack.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 18:48:00 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/27 18:48:00 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	decrease_fuel(t_data *d)
{
	d->player.is_flying -= 1;
	if (!d->player.is_flying)
	{
		if (d->slot1 && d->slot1->is_jetpack)
			d->slot1 = NULL;
		if (d->slot2 && d->slot2->is_jetpack)
			d->slot2 = NULL;
		if (d->slot3 && d->slot3->is_jetpack)
			d->slot3 = NULL;
	}
}
