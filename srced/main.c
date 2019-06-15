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
*/

void	debug_print(t_data *d)
{
	t_monster_list	*tmp;
	int				i;

	ft_printf("%d\n", d->nbmonsters);
	if (d->interface.monster_list)
	{
		tmp = d->interface.monster_list->begin;
		while (tmp)
		{
			ft_printf("%s\n", tmp->name);
			printf("%5.2f %5.2f\n", tmp->pos.x, tmp->pos.y);
			ft_printf("sector : %d\n", tmp->sectnunm);
			tmp = tmp->next;
		}
	}
	i = -1;
	while (++i < 4)
		ft_printf("%s\n", d->assets_data[i].file);
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
			event_motion_mouse(d, &e);
		draw_screen(d);
		SDL_FlushEvent(SDL_MOUSEMOTION);
	}
	SDL_DestroyWindow(d->win);
	SDL_Quit();
	return ((open == -2) ? 1 : 0);
}

int		main(int ac, char **av)
{
	t_data	d;
	pid_t	pid;
	char	**argv;
	char	**env;
// TODO open new map with argv[1], will be used to save the new map under that name
// ./editor "with argument" will be mandatory
// to open existing map or new one
// save the name in current_loaded_map
// need difference between new map in argv[1] and existing map
// parse folder and find is file already exist
// load it if yes, create it if no
	init_data(&d);
	if (init_editor(&d))
		return (EXIT_FAILURE);
	if (ac == 1)
		init_sectors(&d);
	else if (ac == 2)
		load_map(&d, (d.current_loaded_map = av[1]));
	if (event_loop(&d))
	{
		argv = (char*[]){"editor", d.map_to_open, NULL};
		pid = fork();
		if (pid == 0)
			execve((const char*)argv[0], (char *const *)argv, env);
		else
			return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
