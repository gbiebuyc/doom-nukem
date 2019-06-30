/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 14:03:55 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/29 20:45:22 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	help_screen(t_data *d)
{
	SDL_Event	e;
	int	count;

	ft_memset(d->screen->pixels, 0, d->screen->pitch * d->screen->h);
	draw_string(d, (t_font){
			"WASD / ZQSD   Move\n"
			"Ctrl          Crouch\n"
			"Space         Jump / Jetpack\n"
			"1             Cryo Ballista\n"
			"2             Blaster\n"
			"3             M16\n",
			WIDTH / 2 - 150, HEIGHT / 2 - 120, 0, 2});
	SDL_UpdateWindowSurface(d->win);
	count = 0;
	while (SDL_WaitEvent(&e))
	{
		if (e.key.keysym.sym == SDLK_RETURN && e.type == SDL_KEYUP)
			count++;
		if (e.key.keysym.sym == SDLK_ESCAPE && e.type == SDL_KEYUP)
			count++;
		if (count > 1)
			return ;
	}
}
