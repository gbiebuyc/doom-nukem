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
		/* 	if (read(f, &d->monsters[i].pos, sizeof(t_vec2f)) < 0 ||
				read(f, &d->monsters[i].size, sizeof(double)) < 0 ||
				read(f, &d->monsters[i].health_mult, sizeof(double)) < 0 ||
				read(f, &d->monsters[i].rot, sizeof(double)) < 0 ||
				read(f, &d->monsters[i].cursectnum, sizeof(int16_t)) < 0 ||
				read(f, &d->monsters[i].id_type, sizeof(uint8_t)) < 0 ||
				read(f, &d->monsters[i].anim_state, sizeof(uint8_t)) < 0 ||
				read(f, &d->monsters[i].anim_time, sizeof(uint8_t)) < 0 ||
				read(f, &d->monsters[i].behaviour, sizeof(uint8_t)) < 0 ||
				read(f, &d->monsters[i].timer, sizeof(uint8_t)) < 0 ||
				read(f, &d->monsters[i].life, sizeof(int16_t)) < 0 ||
				read(f, &d->monsters[i].height, sizeof(double)) < 0 ||
				read(f, &d->monsters[i].width, sizeof(double)) < 0 ||
				read(f, &d->monsters[i].can_collide, sizeof(bool)) < 0 ||
				read(f, &d->monsters[i].activated, sizeof(bool)) < 0)
				return (ft_printf("Failed to read monsters\n"));*/
				
		// if (read(f, &d->monsters, sizeof(d->monsters)) < 0)
		// 	return (ft_printf("Failed to read monsters.\n"));
	}
	return (0);
}
