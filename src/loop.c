/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 01:36:33 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 06:47:25 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** problematique : besoin de faire un while(1) qui ne consomme pas tout le CPU.
** Le temps de rafraichissement est defini via clock() et usleep() permet de 
** mettre en pause le programme MAIS usleep() met en standby le refresh dec lock()
** et n'est donc pas fiable
*/

static inline void	check_time(double *time)
{
	static int count = 0; //remove for frame count

	if (*time > 0.005)
		*time = 0.005;
	if (*time < 0.0)
	{
		*time = 0.005;
		//add refresh
		printf("%d\n", count++); // do a time ./doom, press esc at 600 and you get the gramerate
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
	static double	time = 0.005; // good value = 0.015, 0.005==merde mais qui consomme pas cpu

	set_time(&time);
	check_time(&time);
	if (time > 0.0001)
	usleep((useconds_t) (time * 14000)); //random value pifometre
	while (SDL_PollEvent(&d->events)) 
//	if (time > 0 && SDL_WaitEventTimeout(&d->events, (int) (time * 110))) //opti cpu ???
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
}
