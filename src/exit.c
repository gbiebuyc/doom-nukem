/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 00:00:29 by nallani           #+#    #+#             */
/*   Updated: 2019/06/27 01:49:29 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	proper_exit(t_data *d)
{
	invoke_msg(d, "EXITING...");
	render(d);
	d->musicnum = -1;
	if (pthread_join(d->music_thread, NULL))
		printf("pthread_join error\n");
	SDL_DestroyWindow(d->win);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

void	err_exit(t_data *d, char count, const char *msg)
{
	ft_putendl_fd(msg, 2);
	ft_putstr_fd("err_code: ", 2);
	ft_putnbr_fd((int)count, 2);
	ft_putstr_fd("\n", 2);
	if (count > 5)
		SDL_FreeSurface(d->textures[3]);
	if (count > 4)
		SDL_FreeSurface(d->textures[2]);
	if (count > 3)
		SDL_FreeSurface(d->textures[1]);
	if (count > 2)
		SDL_FreeSurface(d->textures[0]);
	if (count > 1)
		SDL_DestroyWindow(d->win);
	if (count)
		SDL_Quit();
	exit(EXIT_FAILURE);
}
