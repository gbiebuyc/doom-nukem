/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 01:36:33 by nallani           #+#    #+#             */
/*   Updated: 2019/05/17 19:55:43 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	print_fps(void)
{
	static int		i;
	static uint32_t	last;

	if (SDL_GetTicks() - last > 1000)
	{
		printf("%d fps\n", i);
		last = SDL_GetTicks();
		i = 0;
	}
	i++;
}

void	loop(t_data *d)
{
	SDL_Event	e;
	uint32_t	start;

	while (1)
	{
		start = SDL_GetTicks();
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
				event_key_down(d, e.key);
			if (e.type == SDL_MOUSEMOTION)
				event_mouse_motion(d, e.motion);
			if (e.type == SDL_MOUSEBUTTONDOWN ||
					e.type == SDL_MOUSEBUTTONUP)
				event_mouse_button(d, e.button);
			if (e.type == SDL_QUIT)
				proper_exit(d);
		}
		update(d);
		render(d);
		//print_fps();
		if (1000 / FPS > SDL_GetTicks() - start)
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
	}
}
