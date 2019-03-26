/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:39:11 by nallani           #+#    #+#             */
/*   Updated: 2019/03/26 00:41:35 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


int		main(int argc, char **argv)
{	
	t_data d;

	(void)argc;
	(void)argv; // parse args pour doom-nukem_ed ?
	ft_init_sdl(&d, WIN_WIDTH, WIN_LENGTH);
	ini_player(&d);
	for(int i = 0; i < 600; i++)
		for(int j = 0; j < 800; j++)
			((uint32_t*)d.main_win.surface->pixels)[i * 800 + j] =
				SDL_MapRGBA(d.main_win.surface->format, 0, (uint8_t)j, (uint8_t)i, 255);
	gettimeofday(&d.time.tod, NULL); // si besoin de timer reel
	d.time.ini_time = d.time.tod; // pareil
	while (19)
		loop(&d);
}
