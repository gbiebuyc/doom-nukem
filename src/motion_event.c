/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:33:28 by nallani           #+#    #+#             */
/*   Updated: 2019/04/21 23:38:28 by gbiebuyc         ###   ########.fr       */
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
	d->cam.y_offset =
		ft_max(-MAX_Y_OFFSET, ft_min(MAX_Y_OFFSET, d->cam.y_offset));
	d->cam.rot += event.xrel * MOUSE_SENSITIVTY * 0.001;
}
