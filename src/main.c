/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:39:11 by nallani           #+#    #+#             */
/*   Updated: 2019/06/22 13:52:03 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	init_everything(t_data *d, char *map)
{
	//strcpy(d->nextmap, "newmap.DNMAP");
	load_map(d, map);
	fix_picnum(d);
	init_player(d, &d->player);
	init_monsters(d);
	init_projectiles(d);
	if (d->startsectnum < 0)
		exit(ft_printf("bad startsectnum\n"));
	/*** music thread ***/
	d->musicnum = (d->musicnum + 1) % 2;
	t_sound_thread_arg arg = {d, true};
	if (pthread_create(&d->music_thread, NULL, sound_thread, &arg))
		ft_printf("pthread_create error\n");
	/***/
	loop(d);
}

int		main(int ac, char **av)
{	
	t_data d;

	if (ac > 2)
	{
		ft_printf("Usage : ./doom-nukem \"Map_name\"\n");
		ft_printf("The map must be in the \"maps\" folder.\n");
		exit(EXIT_FAILURE);
	}
	if (chdir(SDL_GetBasePath()) < 0)
		ft_printf("error\n");
	init_font(&d);
	init_sdl(&d);
	init_everything(&d, (ac == 2) ? av[1] : "newmap.DNMAP");
	return (EXIT_SUCCESS);
}
