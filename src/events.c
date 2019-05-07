/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 04:14:37 by nallani           #+#    #+#             */
/*   Updated: 2019/04/29 01:23:16 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	event_key_down(t_data *d, SDL_KeyboardEvent event)
{
	if (event.keysym.sym == SDLK_ESCAPE)
		proper_exit(d);

	// Pause button
	else if (event.keysym.sym == SDLK_p)
		 SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode());
	else if (event.keysym.sym == SDLK_PAUSE)
		d->debug_pause = true;
}

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

void	event_mouse_button(t_data *d, SDL_MouseButtonEvent event)
{
	(void)d;
	if (event.state == SDL_PRESSED)
	{
	}
	else
	{
	}
}

void debug_pause(t_data *d)
{
	SDL_Event	e;

	if (!d->debug_pause)
		return ;
	SDL_UpdateWindowSurface(d->win);
	while (SDL_WaitEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_SPACE)
				return ;
			else if (e.key.keysym.sym == SDLK_PAUSE)
			{
				d->debug_pause = false;
				return ;
			}
			else if (e.key.keysym.sym == SDLK_ESCAPE)
				exit(EXIT_SUCCESS);
		}
	}
}
