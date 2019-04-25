/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:33:28 by nallani           #+#    #+#             */
/*   Updated: 2019/04/26 16:35:08 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MOUSE_SENSITIVTY 1
#define MAX_Y_OFFSET HEIGHT/2

void		event_mouse_motion(t_data *d, SDL_MouseMotionEvent event)
{
	if (SDL_GetRelativeMouseMode() == SDL_FALSE)
		return ;
	d->cam.y_offset += event.yrel * MOUSE_SENSITIVTY * 0.3;
	d->cam.y_offset = fclamp(d->cam.y_offset, -MAX_Y_OFFSET, MAX_Y_OFFSET);
	d->cam.rot += event.xrel * MOUSE_SENSITIVTY * 0.001;
}
