/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 00:00:29 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 08:46:54 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	proper_exit(t_data *d)
{
	SDL_DestroyWindow(d->main_win.win);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}
//SDL_DestroyWindow(SDL_Window *window);
//SDL_FreeSurface(SDL_Surface *surface); // DO_NOT_USE_WITH_SURFACE_FROM_GetWindowSurface();

void	err_exit(t_data *d, char count, const char *msg)
{
	ft_putendl_fd(msg, 2);
	if (count > 1)
		SDL_DestroyWindow(d->main_win.win);
	if (count)
		SDL_Quit();
	exit(EXIT_FAILURE);
}
