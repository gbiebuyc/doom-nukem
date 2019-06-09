/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:04:36 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/09 17:04:37 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		read_monsters_data(t_data *d, int f)
{
	int	i;

	if (read(f, &d->nummonsters, sizeof(uint16_t)) < 0)
		return (ft_printf("Failed to read nummonsters.\n"));
	if (d->nummonsters > 0)
	{
		if (!(d->monsters = (t_monster*)malloc(sizeof(t_monster) *
														d->nummonsters)))
			return (ft_printf("Failed to allocate monster stucture.n"));
		i = -1;
		while (++i < d->nummonsters)
			 if (read(f, &d->monsters[i], sizeof(t_monster)) < 0)
			 	return (ft_printf("Failed to read monsters.\n"));
	}
	return (0);
}
