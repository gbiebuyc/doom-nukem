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

int		map_exist(t_data *d, char *map)
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
			ft_strcpy(d->current_loaded_map,
						d->interface.map_list_sort[i]->name);
			if (!have_extension)
				free(check);
			return (1);
		}
	ft_strcpy(d->current_loaded_map, map);
	if (!have_extension)
		free(check);
	return (0);
}

/*
**	t_wall		*wall;
**	int			w;
**	int			s;
**
**	w = 0;
**	s = 0;
**	while (w < d->numwalls)
**	{
**		wall = d->walls + w;
**		if (w == d->sectors[s].firstwallnum)
**			ft_printf("++++++\nsector %d\n++++++\n", s++);
**		ft_printf("numwalls : %d\n", d->sectors[s].numwalls);
**		ft_printf("------\nwall %d\n------\n", w);
**		ft_printf("neighbor : %d\n", wall->neighborsect);
**		ft_printf("picnum : %d\n", wall->middlepicnum);
**		ft_printf("texture name = %s\n", wall->texture_name);
**		w++;
**	}
**
**	t_monster_list	*tmp;
**	int				i;
**
**	ft_printf("%d\n", d->nbmonsters);
**	if (d->interface.monster_list)
**	{
**		tmp = d->interface.monster_list->begin;
**		while (tmp)
**		{
**			ft_printf("%s\n", tmp->name);
**			printf("%5.2f %5.2f\n", tmp->pos.x, tmp->pos.y);
**			ft_printf("sector : %d\n", tmp->sectnunm);
**			tmp = tmp->next;
**		}
**	}
**	i = -1;
**	while (++i < NB_CATEGORY)
**		ft_printf("%s\n", d->assets_data[i].file);
**	ft_printf("player pos : %f %f %f\n", d->player_start.x,
**						d->player_start.y, d->player_start.z);
**	ft_printf("start sect : %d\n", d->startsectnum);
*/

void	debug_print(t_data *d)
{
	t_assets_list	*tmp;

	ft_printf("%d\n", d->nb_assets);
	if (d->interface.assets_list)
	{
		tmp = d->interface.assets_list->begin;
		while (tmp)
		{
			ft_printf("asset num : %d\n", tmp->num_asset);
			ft_printf("asset picnum : %d\n", tmp->picnum);
			printf("%5.2f %5.2f\n", tmp->world_pos.x, tmp->world_pos.y);
			ft_printf("sector : %d\n", tmp->sectnunm);
			ft_printf("is on floor : %d\n", tmp->is_on_floor);
			ft_printf("is on ceil : %d\n", tmp->is_on_ceil);
			ft_printf("stat : \n");
			ft_printf("Heal : %d\n", tmp->stat_mod.heal);
			ft_printf("Damage : %d\n", tmp->stat_mod.damage);
			ft_printf("ballista_ammo : %d\n", tmp->stat_mod.ballista_ammo);
			ft_printf("blaster_ammo : %d\n", tmp->stat_mod.blaster_ammo);
			ft_printf("m16_ammo : %d\n", tmp->stat_mod.m16_ammo);
			ft_printf("is interactive : %d\n", tmp->is_interactive);
			ft_printf("is autopick : %d\n", tmp->is_autopick);
			ft_printf("collision : %d\n", tmp->collision);
			tmp = tmp->next;
		}
	}
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
	if (ac == 1 || (ac == 2 && !map_exist(&d, av[1])))
		init_sectors(&d);
	else if (ac == 2)
		if (load_map(&d, d.current_loaded_map))
			return (ed_usage(&d));
	// TODO if next_map doesn't exist, reset d->next_map
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
