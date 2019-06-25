/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 01:48:46 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/14 19:01:07 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		ed_usage(t_data *d)
{
	int	i;

	get_map_list(d);
	ft_printf("# ##########################################");
	ft_printf("########################################### #\n");
	ft_printf("# usage : ./editor [MAP_NAME] \t\t\t\t\t\t\t\t#\n");
	ft_printf("#\t- The MAP_NAME must be the name of a map inside the");
	ft_printf(" \"maps\" direcotry.\t\t#\n");
	ft_printf("#\t- example :\t\t\t\t\t\t\t\t\t#\n");
	ft_printf("#\t\t You can specify the name directly : ");
	ft_printf("./editor map01.DNMAP\t\t#\n");
	ft_printf("#\t\t Or you can specify the path with map_name : ");
	ft_printf("./editor maps/map01.DNMAP\t#\n");
	ft_printf("# ##########################################");
	ft_printf("########################################### #\n");
	ft_printf("# Current map list : \t\t\t\t\t\t\t\t\t\n");
	i = -1;
	while (++i < d->interface.nb_map)
		ft_printf("# \t- %s\n", d->interface.map_list_sort[i]->name);
	return (EXIT_FAILURE);
}

int		map_exist(t_data *d, char *map, char *save)
{
	int		i;
	char	*check;
	int		len;
	int		have_extension;

	len = (int)ft_strlen(map);
	have_extension = (len < 7) ? 0 : ft_strequ(&map[len - 6], ".DNMAP");
	check = (contain_map_path(map) == 1) ? &map[5] : map;
	check = (contain_map_path(map) == 2) ? &map[7] : check;
	check = (!have_extension) ? ft_strjoin(check, ".DNMAP") : check;
	get_map_list(d);
	i = -1;
	while (++i < d->interface.nb_map)
		if (ft_strequ(check, d->interface.map_list_sort[i]->name))
		{
			ft_strcpy(save,
						d->interface.map_list_sort[i]->name);
			if (!have_extension)
				free(check);
			return (1);
		}
	ft_strcpy(save, map);
	if (!have_extension)
		free(check);
	return (0);
}

int		event_loop(t_data *d)
{
	SDL_Event	e;
	int			open;

	open = 0;
	draw_screen(d);
	while (SDL_WaitEvent(&e))
	{
		if (e.type == SDL_QUIT)
			break ;
		else if (e.type == SDL_KEYUP)
			event_key_up(d, e.key.keysym.sym);
		else if (e.type == SDL_KEYDOWN)
			event_key_down(d, e.key.keysym.sym);
		else if (e.type == SDL_MOUSEWHEEL)
			mouse_wheel(d, &e);
		else if ((open = event_mouse_button(d, &e)) < 0)
			break ;
		else if (e.type == SDL_MOUSEMOTION)
			event_motion_mouse(d, &e, 0, 0);
		draw_screen(d);
		SDL_FlushEvent(SDL_MOUSEMOTION);
	}
	SDL_DestroyWindow(d->win);
	SDL_Quit();
	return ((open == -2) ? 1 : 0);
}

int		main(int ac, char **av)
{
	t_data		d;
	pid_t		pid;
	char		**argv;
	extern char	**environ;

	init_data(&d);
	if (init_editor(&d))
		return (EXIT_FAILURE);
	if (ac == 1 || (ac == 2 && !map_exist(&d, av[1], d.current_loaded_map)))
		init_sectors(&d);
	else if (ac == 2)
		if (load_map(&d, d.current_loaded_map))
			return (ed_usage(&d));
	if ((ac == 1 || ac == 2) && event_loop(&d))
	{
		argv = (char*[]){"editor", d.map_to_open, NULL};
		pid = fork();
		if (pid == 0)
			execve((const char*)argv[0], (char *const *)argv, environ);
		else
			return (EXIT_SUCCESS);
	}
	else if (ac != 1 && ac != 2)
		ed_usage(&d);
	return (EXIT_SUCCESS);
}
