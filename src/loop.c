/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 01:36:33 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 04:20:33 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static inline void	check_time(double *time)
{
	if (*time > 0.016)
		*time = 0.015;
	if (*time < 0)
	{
		*time += 0.015;
		//add refresh
	}
}

static inline void	set_time(double *time)
{
	double			time_tmp;
	static double	last_time = 0.0;

	time_tmp = (double)clock() / CLOCK_PER_SEC;
	*time = *time - time_tmp + last_time;
	last_time = time_tmp;
}

void				loop(t_data *d)
{
	static double	time = 0.015;

	set_time(&time);
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
	check_time(&time);
}
