/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:39:11 by nallani           #+#    #+#             */
/*   Updated: 2019/06/26 00:10:48 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	start_music(t_data *d)
{
	static t_sound_thread_arg arg;

	d->musicnum = 0;
	arg = (t_sound_thread_arg){d, .is_music = true};
	if (pthread_create(&d->music_thread, NULL, sound_thread, &arg))
		ft_printf("pthread_create error\n");
}

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
	if (!d->music_thread)
		start_music(d);
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
	intro_screen(&d);
	init_everything(&d, (ac == 2) ? av[1] : "newmap.DNMAP");
	return (EXIT_SUCCESS);
}
