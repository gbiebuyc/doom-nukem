/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 13:22:51 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/30 16:49:09 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define NB_MENU_ITEMS 3

static void	redraw(t_data *d, int choice)
{
	static char buf[] = "  PLAY\n  HELP\n  EXIT";

	buf[0] = (choice == 0) ? '>' : ' ';
	buf[7] = (choice == 1) ? '>' : ' ';
	buf[14] = (choice == 2) ? '>' : ' ';
	ft_memset(d->screen->pixels, 0, d->screen->pitch * d->screen->h);
	draw_string(d, (t_font){buf, WIDTH / 2 - 50, HEIGHT / 2 - 80, 0, 2});
	SDL_UpdateWindowSurface(d->win);
}

void		main_menu(t_data *d)
{
	SDL_Event	e;
	static int	choice;

	redraw(d, choice);
	while (SDL_WaitEvent(&e))
	{
		if (e.type == SDL_QUIT)
			exit(EXIT_SUCCESS);
		if ((e.type != SDL_KEYDOWN) || e.key.repeat)
			continue ;
		if (e.key.keysym.sym == SDLK_UP)
			choice = ft_mod((choice - 1), NB_MENU_ITEMS);
		if (e.key.keysym.sym == SDLK_DOWN)
			choice = ft_mod((choice + 1), NB_MENU_ITEMS);
		if (e.key.keysym.sym == SDLK_RETURN && choice == 0)
			difficulty_menu(d, 0);
		if (e.key.keysym.sym == SDLK_RETURN && choice == 1)
			help_screen(d);
		if ((e.key.keysym.sym == SDLK_RETURN && choice == 2) ||
			(e.key.keysym.sym == SDLK_ESCAPE))
			exit(EXIT_SUCCESS);
		redraw(d, choice);
	}
}
