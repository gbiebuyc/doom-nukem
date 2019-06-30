/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 00:10:57 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/30 15:02:23 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		load_sound2(t_data *d, int f)
{
	static int	i;

	d->chunk[i].allocated = 1;
	d->chunk[i].volume = 128;
	if (read(f, &d->chunk[i].alen, sizeof(d->chunk[i].alen)) < 0)
		return (ft_printf("Failed to read wav spec.\n"));
	if (!(d->chunk[i].abuf = malloc(d->chunk[i].alen)))
		return (ft_printf("Failed to malloc sound\n"));
	if (read(f, d->chunk[i].abuf, d->chunk[i].alen) < 0)
		return (ft_printf("Failed to read abuf \n"));
	i++;
	return (0);
}

int		load_sound(t_data *d, int f)
{
	short	i;

	i = 0;
	if (d->chunk[0].alen)
		return (0);
	while (i++ < NB_OF_SOUNDS)
		if (load_sound2(d, f))
			return (1);
	return (0);
}
