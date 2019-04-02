/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 04:14:37 by nallani           #+#    #+#             */
/*   Updated: 2019/04/02 18:42:20 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


void	event_key_down(t_data *d, SDL_KeyboardEvent event)
{
	if (event.keysym.sym == SDLK_ESCAPE)
		proper_exit(d);

	// Pause button
	if (event.keysym.sym == SDLK_p)
		 SDL_SetRelativeMouseMode((SDL_GetRelativeMouseMode() == SDL_TRUE) ?
				 SDL_FALSE : SDL_TRUE);//todo (maybe ?) : pause button, set on esc and add quit opt ?

	// Deplacement
	if (event.keysym.sym == SDLK_w)
		d->keys.dir = FORWARD;
	if (event.keysym.sym == SDLK_s)
		d->keys.dir = BACKWARD;
	if (event.keysym.sym == SDLK_a)
		d->keys.strafe_dir = LEFT_STRAFE;
	if (event.keysym.sym == SDLK_d)
		d->keys.strafe_dir = RIGHT_STRAFE;

	// Tourner
	if (event.keysym.sym == SDLK_LEFT)
		d->keys.hor_turn = LEFT_TURN;
	if (event.keysym.sym == SDLK_RIGHT)
		d->keys.hor_turn = RIGHT_TURN;

	/*
	// Altitude
	if (event.keysym.sym == SDLK_UP)
		d->camera.pos.y += 0.1;
	if (event.keysym.sym == SDLK_DOWN)
		d->camera.pos.y -= 0.1;	
	*/
}

void	event_key_up(t_data *d, SDL_KeyboardEvent event)
{
	// Deplacement
	if (event.keysym.sym == SDLK_w)
		d->keys.dir = 0;
	if (event.keysym.sym == SDLK_s)
		d->keys.dir = 0;
	if (event.keysym.sym == SDLK_a)
		d->keys.strafe_dir = 0;
	if (event.keysym.sym == SDLK_d)
		d->keys.strafe_dir = 0;

	// Tourner
	if (event.keysym.sym == SDLK_LEFT)
		d->keys.hor_turn = 0;
	if (event.keysym.sym == SDLK_RIGHT)
		d->keys.hor_turn = 0;

	/*
	// Altitude
	if (event.keysym.sym == SDLK_UP)
		d->camera.pos.y += 0.1;
	if (event.keysym.sym == SDLK_DOWN)
		d->camera.pos.y -= 0.1;	
	*/
}
