/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 04:14:37 by nallani           #+#    #+#             */
/*   Updated: 2019/06/30 16:51:31 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	event_key_down(t_data *d, SDL_KeyboardEvent event)
{
	if (event.keysym.sym == SDLK_ESCAPE && !event.repeat)
		pause_menu(d);
	else if (event.keysym.sym == SDLK_p)
		pause_menu(d);
	else if (event.keysym.sym == SDLK_PAUSE)
		d->debug_pause = true;
	else if (event.keysym.sym == SDLK_e)
		press_e(d);
}

void	event_key_up(t_data *d, SDL_KeyboardEvent event)
{
	(void)d;
	(void)event;
}

#define MOUSE_SENSITIVTY 1

void	event_mouse_motion(t_data *d, SDL_MouseMotionEvent event)
{
	if (SDL_GetRelativeMouseMode() == SDL_FALSE)
		return ;
	d->cam.y_offset += event.yrel * MOUSE_SENSITIVTY * 0.5;
	d->cam.y_offset = fclamp(d->cam.y_offset, -MAX_Y_OFFSET, MAX_Y_OFFSET);
	d->cam.rot += event.xrel * MOUSE_SENSITIVTY * 0.001;
}

void	event_mouse_button(t_data *d, SDL_MouseButtonEvent event)
{
	(void)d;
	if (event.button == SDL_BUTTON_LEFT)
		d->left_mouse_button = event.state == SDL_PRESSED ?
			MOUSE_PRESSED : MOUSE_RELEASED;
	if (event.button == SDL_BUTTON_RIGHT)
		d->right_mouse_button = event.state == SDL_PRESSED ?
			MOUSE_PRESSED : MOUSE_RELEASED;
	if (event.state == SDL_RELEASED)
	{
	}
}

void	debug_pause(t_data *d)
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
