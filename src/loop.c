/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 01:36:33 by nallani           #+#    #+#             */
/*   Updated: 2019/04/02 18:18:44 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** a new image will be displayed every FRAME milliseconds MAX
** default value is 15000 == 66.6 fps (1 / 0.015)
*/

#define FRAME 15000

static inline void			check_time(suseconds_t *time, t_data *d, suseconds_t *fps_sec_count)
{
//	static int count = 0; //remove for frame count
	static short fps_count = 0;

	if (*time > FRAME)
		*time = FRAME;
	if (*time <= 0)
	{
		*fps_sec_count = *fps_sec_count - FRAME + *time;
		if (*fps_sec_count <= 0)
		{
			ft_putstr("\r");
			ft_putstr("fps: ");
			ft_putnbr(fps_count);
			fps_count = 0;
			*fps_sec_count = 1000000;
		}
		fps_count++;
		*time = FRAME;
		refresh_game(d);
		refresh_img(d);
		(void)d;
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

	i = FRAME - FRAME / 15;
	while (i > FRAME / 16) // a voir avec opti
	{
		if (*time > i)
		{
			usleep(i - FRAME / 60);
			return ;
		}
		i -= FRAME / 30;
	}
}

static inline void			set_time(suseconds_t *time, t_data *d)
{
	gettimeofday(&d->time.tod, NULL);
	*time -= get_time(d->time.tod);
}

void						loop(t_data *d)
{
	static suseconds_t	time = FRAME;
	static suseconds_t	fps_sec_count = 1000000;

	set_time(&time, d);
	opti_sleep(&time);
	while (SDL_PollEvent(&d->events))
	{
		if (d->events.type == SDL_KEYDOWN)
			event_key_down(d, d->events.key);
		if (d->events.type == SDL_KEYUP)
			event_key_up(d, d->events.key);
		if (d->events.type == SDL_MOUSEMOTION)
			event_mouse_motion(d, d->events.motion);
		if (d->events.type == SDL_MOUSEBUTTONDOWN || d->events.type == SDL_MOUSEBUTTONUP)
			event_mouse_button(d, d->events.button);
		if (d->events.type == SDL_WINDOWEVENT)
			event_window(d, d->events.window);
		if (d->events.type == SDL_QUIT) // needed somewhere ?
			proper_exit(d);
	}
	check_time(&time, d, &fps_sec_count);
}
