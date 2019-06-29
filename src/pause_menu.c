/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:33:40 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/29 15:33:40 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define NB_MENU_ITEMS 2

static void	redraw(t_data *d, int choice)
{
	static char buf[] = "  HELP\n  EXIT";

	buf[0] = (choice == 0) ? '>' : ' ';
	buf[7] = (choice == 1) ? '>' : ' ';
	ft_memset(d->screen->pixels, 0, d->screen->pitch * d->screen->h);
	draw_string(d, (t_font){buf, WIDTH / 2 - 50, HEIGHT / 2 - 60, 0, 2});
	SDL_UpdateWindowSurface(d->win);
}

void		pause_menu(t_data *d)
{
	SDL_Event	e;
	static int	choice;

	if (SDL_SetRelativeMouseMode(SDL_FALSE) == -1)
		ft_printf("SDL_SetRelativeMouseMode error");
	redraw(d, choice);
	while (SDL_WaitEvent(&e))
	{
		if (e.type != SDL_KEYDOWN)
			continue ;
		if (e.key.keysym.sym == SDLK_UP)
			choice = ft_mod((choice - 1), NB_MENU_ITEMS);
		if (e.key.keysym.sym == SDLK_DOWN)
			choice = ft_mod((choice + 1), NB_MENU_ITEMS);
		if (e.key.keysym.sym == SDLK_RETURN && choice == 0)
			help_screen(d);
		if (e.key.keysym.sym == SDLK_RETURN && choice == 1)
			proper_exit(d);
		if (e.key.keysym.sym == SDLK_ESCAPE)
			return ((void)SDL_SetRelativeMouseMode(SDL_TRUE));
		redraw(d, choice);
	}
}
