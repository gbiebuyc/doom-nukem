/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:33:28 by nallani           #+#    #+#             */
/*   Updated: 2019/04/05 17:43:55 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MOUSE_SENSITIVTY 0.001

void		event_mouse_motion(t_data *d, SDL_MouseMotionEvent event)
{
	if (SDL_GetRelativeMouseMode() == SDL_FALSE)
		return ;
	d->cam.rot.x -= event.yrel * MOUSE_SENSITIVTY;
	d->cam.rot.y += event.xrel * MOUSE_SENSITIVTY;
}
