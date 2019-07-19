/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 14:03:55 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/07/09 22:17:32 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	help_screen(t_data *d)
{
	SDL_Event	e;

	ft_memset(d->screen->pixels, 0, d->screen->pitch * d->screen->h);
	draw_string(d, (t_font){
			"E             Open doors / pickup items\n"
			"WASD / ZQSD   Move\n"
			"Ctrl          Crouch\n"
			"Space         Jump / Jetpack\n"
			"1             Cryo Ballista\n"
			"2             Blaster\n"
			"3             M16\n",
			WIDTH / 2 - 150, HEIGHT / 2 - 120, 0xffffff, 2});
	SDL_UpdateWindowSurface(d->win);
	while (SDL_WaitEvent(&e))
	{
		if (e.type == SDL_QUIT)
			exit(EXIT_SUCCESS);
		if ((e.type != SDL_KEYDOWN) || e.key.repeat)
			continue ;
		else if (e.key.keysym.sym == SDLK_RETURN)
			return ;
		else if (e.key.keysym.sym == SDLK_ESCAPE)
			return ;
	}
}
