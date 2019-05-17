/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 02:56:31 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/07 01:12:11 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	read_pointer(char **p, void *dst, size_t size)
{
	ft_memcpy(dst, *p, size);
	*p += size;
}

void	load_map(t_data *d, char *p)
{
	// Load starting position
	read_pointer(&p, &d->cam.pos, sizeof(t_vec3f));
	read_pointer(&p, &d->cam.rot, sizeof(double));
	read_pointer(&p, &d->cursectnum, sizeof(int16_t));

	// Load all sectors
	read_pointer(&p, &d->numsectors, sizeof(int16_t));
	read_pointer(&p, d->sectors, sizeof(t_sector) * d->numsectors);

	// Load all walls
	read_pointer(&p, &d->numwalls, sizeof(int16_t));
	read_pointer(&p, d->walls, sizeof(t_wall) * d->numwalls);

	// Load ennemy data
	read_pointer(&p, &d->nummonsters, sizeof(d->nummonsters));
	read_pointer(&p, d->monsters, sizeof(t_monster) * d->nummonsters);
}
