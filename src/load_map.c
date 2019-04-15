/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 02:56:31 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/15 05:29:14 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	load_map(t_data *d)
{
	int f;
	
	if (
			((f = open("map01", O_RDONLY)) == -1) ||

			// Load starting position
			read(f, &d->cam.pos, sizeof(t_vec3f)) == -1 ||
			read(f, &d->cam.rot.y, sizeof(double)) == -1 ||

			// Load all sectors
			read(f, &d->numsectors, sizeof(int16_t)) == -1 ||
			read(f, d->sectors, sizeof(t_sector) * d->numsectors) == -1 ||

			// Load all walls
			read(f, &d->numwalls, sizeof(int16_t)) == -1 ||
			read(f, d->walls, sizeof(t_wall) * d->numwalls) == -1
	   )
	{
		printf("map error\n");
		exit(EXIT_FAILURE);
	}
	close(f);
}
