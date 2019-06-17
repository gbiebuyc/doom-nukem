/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:39:11 by nallani           #+#    #+#             */
/*   Updated: 2019/06/06 20:18:14 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		main(int ac, char **av)
{	
	t_data d;

	if (ac == 1 || ac == 2)
	{
		init_font(&d);
		load_map(&d, (ac == 2) ? av[1] : "newmap.DNMAP");
		init_sdl(&d);
		init_player(&d, &d.player);
		init_monsters(&d);
		init_projectiles(&d);
		if (d.cursectnum < 0)
			exit(ft_printf("bad startsectnum\n"));
		loop(&d);
	}
	else
	{
		ft_printf("Usage : ./doom-nukem \"Map_name\"\n");
		ft_printf("The map must be in the \"maps\" folder.\n");
	}
	return (EXIT_SUCCESS);
}
