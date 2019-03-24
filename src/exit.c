/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 00:00:29 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 01:35:56 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	proper_exit(t_data *d)
{
	SDL_DestroyWindow(d->main_win.win);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}
