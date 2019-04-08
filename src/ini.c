/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 22:50:25 by nallani           #+#    #+#             */
/*   Updated: 2019/04/08 05:50:03 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ini_player(t_data *d)
{
	d->cam.pos = (t_vec3f){-4.5, 4.5, -8.75};
	d->cam.rot = (t_vec3f){-0.42, 0.5, 0};
}

void	init_scene(t_data *d)
{
	t_vec3f cube[8];

	cube[0] = (t_vec3f){-1, 1, 1};
	cube[1] = (t_vec3f){1, 1, 1};
	cube[2] = (t_vec3f){1, -1, 1};
	cube[3] = (t_vec3f){-1, -1, 1};
	cube[4] = (t_vec3f){-1, 1, -1};
	cube[5] = (t_vec3f){1, 1, -1};
	cube[6] = (t_vec3f){1, -1, -1};
	cube[7] = (t_vec3f){-1, -1, -1};

	d->walls[0] = (t_wall){cube[0], cube[1], cube[2], cube[3]};
	d->walls[1] = (t_wall){cube[1], cube[5], cube[6], cube[2]};
	d->walls[2] = (t_wall){cube[4], cube[0], cube[3], cube[7]};
	d->walls[3] = (t_wall){cube[5], cube[4], cube[7], cube[6]};
}
