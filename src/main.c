/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:39:11 by nallani           #+#    #+#             */
/*   Updated: 2019/06/30 19:21:09 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	init_everything(t_data *d, char *map)
{
	int i;
	int	j;
	int	k;

	i = -1;
	while (++i < MAXTYPEMONSTERS && (j = -1))
		while (++j < MAX_STATE_MONSTER && (k = -1))
			while (++k < MAXNBOFANIMATION)
				d->monster_text[i][j][k] = NULL;
	load_map(d, map);
	fix_picnum(d);
	init_player(d, &d->player);
	init_monsters(d);
	init_projectiles(d);
	init_player(d, &d->player);
	if (d->startsectnum < 0)
		exit(ft_printf("bad startsectnum\n"));
	if (SDL_SetRelativeMouseMode(SDL_TRUE) == -1)
		ft_printf("SDL_SetRelativeMouseMode error");
	play_music(d, MAIN_MUSIC);
	fix_neighborsects(d);
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
	init_font(&d);
	init_sdl(&d);
	if (!(d.zbuffer = malloc(sizeof(double) * WIDTH * HEIGHT)))
		exit(ft_printf("malloc zbuffer_sprites failed.\n"));
	ft_strcpy(d.nextmap, (ac == 2) ? av[1] : "newmap.DNMAP");
	if (ft_strequ(d.nextmap, "./maps/newmap.DNMAP"))
		init_everything(&d, d.nextmap);
	else
		main_menu(&d);
	return (EXIT_SUCCESS);
}
