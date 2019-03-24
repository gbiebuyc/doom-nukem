/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 01:36:33 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 08:00:27 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static inline void			check_time(suseconds_t *time)
{
	static int count = 0; //remove for frame count

	if (*time > 15000)
		*time = 15000;
	if (*time < 0)
	{
		*time = 15000;
		//add refresh
		printf("count:%d\n", count++); // do a time ./doom, press esc at 600 and you get the gramerate
	}
}

static inline suseconds_t	get_time(struct timeval new)
{
	static struct timeval	tmp = {0, 0};
	suseconds_t				value;

	if (!(tmp.tv_sec))
	{
		tmp = new;
		return (0);
	}
	else
	{
		if (new.tv_sec > tmp.tv_sec)
		{
			value = 1000 + new.tv_usec - tmp.tv_usec;
		}
		else
		{
			value = new.tv_usec - tmp.tv_usec;
		}
		tmp = new;
	}
	return (value);
}

static inline void			opti_sleep(suseconds_t *time)
{
	suseconds_t		i;

	i = 14000;
	while (i > 900)
	{
		if (*time > i)
		{
			usleep(i - 250);
			return ;
		}
		i -= 500;
	}
}

static inline void			set_time(suseconds_t *time, t_data *d)
{
	gettimeofday(&d->time.tod, NULL);
	*time -= get_time(d->time.tod);
}

void						loop(t_data *d)
{
	static suseconds_t	time = 15000; // good value = 0.015, 0.005==merde mais qui consomme pas cpu

	set_time(&time, d);
	check_time(&time);
	opti_sleep(&time);
	if (time > 900)
		usleep(750);
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
