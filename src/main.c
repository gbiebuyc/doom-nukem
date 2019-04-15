/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:39:11 by nallani           #+#    #+#             */
/*   Updated: 2019/04/15 05:29:31 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


int		main(int argc, char **argv)
{	
	t_data d;

	d = (t_data){.keys.dir = 0, .keys.strafe_dir = 0};
	(void)argc;
	(void)argv; // parse args pour doom-nukem_ed ?
	load_map(&d);
	ft_init_sdl(&d, WIN_WIDTH, WIN_LENGTH);
	gettimeofday(&d.time.tod, NULL); // si besoin de timer reel
	d.time.ini_time = d.time.tod; // pareil
	while (19)
		loop(&d);
}
