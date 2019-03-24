/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 01:36:33 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 03:41:16 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	event_key_down(t_data *d, SDL_KeyboardEvent event)
{
	if (event.keysym.sym == SDLK_ESCAPE)
		proper_exit(d);
}

void	event_window(t_data *d, SDL_WindowEvent event)
{
	if (event.event == SDL_WINDOWEVENT_CLOSE)
		proper_exit(d);
}

static inline void reset_time(double *time)
{
	if (*time > 0.016)
		*time = 0.015;
	if (*time < 0)
	{
		//refresh avant ou apres ?
		*time += 0.015;
	}
}

void	loop(t_data *d)
{
	static double	time = 0.015;
	double			time_tmp;

	time_tmp = (clock())/CLOCK_PER_SEC;
	time = time - time_tmp + d->time.last_time;
	d->time.last_time = time_tmp;
	printf("%f\n", time_tmp);
	if (time > 0)
		if (SDL_PollEvent(&d->events))
		{
			if (d->events.type == SDL_KEYDOWN) 
				event_key_down(d, d->events.key);
			if (d->events.type == SDL_KEYUP)
				;
			if (d->events.type == SDL_MOUSEMOTION)
				;
			if (d->events.type == SDL_MOUSEBUTTONDOWN)
				;
			if (d->events.type == SDL_MOUSEBUTTONUP)
				;
			if (d->events.type == SDL_WINDOWEVENT)
				event_window(d, d->events.window);
			if (d->events.type == SDL_QUIT) // needed somewhere ?
				proper_exit(d);
		}
	reset_time(&time);
}
