/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:33:28 by nallani           #+#    #+#             */
/*   Updated: 2019/04/02 16:47:41 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	actualize_dir_vec3f_x(double diff, t_vec3f *dir)
{
	double	x;
	double	y;
	double	z;

	x = dir->x;
	y = dir->y;
	z = dir->z;
	dir->x = x * cos(diff) - z * sin(diff);
	dir->z = x * sin(diff) + z * cos(diff);
	x = dir->x;
	z = dir->z;
}

#define MOUSE_SENSITIVTY 0.1

void		event_mouse_motion(t_data *d, SDL_MouseMotionEvent event)
{
	if (SDL_GetRelativeMouseMode() == SDL_FALSE)
		return ;
	if (event.xrel)
	actualize_dir_vec3f_x(0.0174533 * event.xrel * MOUSE_SENSITIVTY, &d->camera.dir);
}
