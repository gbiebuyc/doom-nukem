/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 10:09:45 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/29 10:09:45 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define NB_MENU_ITEMS 3

void	redraw(t_data *d, int choice)
{
	static char buf[] = "  I'M TOO YOUNG TO DIE.\n"
		"  HEY, NOT TOO ROUGH.\n  HURT ME PLENTY.";

	buf[0] = (choice == 0) ? '>' : ' ';
	buf[24] = (choice == 1) ? '>' : ' ';
	buf[46] = (choice == 2) ? '>' : ' ';
	ft_memset(d->screen->pixels, 0, d->screen->pitch * d->screen->h);
	draw_string(d, (t_font){buf, WIDTH / 2 - 150, HEIGHT / 2 - 80, 0, 2});
	SDL_UpdateWindowSurface(d->win);
}

int		ft_mod(int i, int n)
{
	return ((i % n + n) % n);
}

int		menu_screen(t_data *d)
{
	SDL_Event	e;
	int			choice;

	choice = 1;
	redraw(d, choice);
	while (SDL_WaitEvent(&e))
	{
		if (e.type != SDL_KEYDOWN)
			continue ;
		if (e.key.keysym.sym == SDLK_UP)
			redraw(d, (choice = ft_mod((choice - 1), NB_MENU_ITEMS)));
		if (e.key.keysym.sym == SDLK_DOWN)
			redraw(d, (choice = ft_mod((choice + 1), NB_MENU_ITEMS)));
		if (e.key.keysym.sym == SDLK_RETURN)
			return (choice);
		if (e.key.keysym.sym == SDLK_ESCAPE)
			exit(EXIT_SUCCESS);
	}
	return (choice);
}
