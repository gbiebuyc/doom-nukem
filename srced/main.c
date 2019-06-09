/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 01:48:46 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/06 19:54:41 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		debug_print(t_data *d)
{
	t_monster_list	*tmp;

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
/*	t_wall		*wall;
	int			w;
	int			s;

	w = 0;
	s = 0;
	while (w < d->numwalls)
	{
		wall = d->walls + w;
		if (w == d->sectors[s].firstwallnum)
			ft_printf("++++++\nsector %d\n++++++\n", s++);
		ft_printf("numwalls : %d\n", d->sectors[s].numwalls);
		ft_printf("------\nwall %d\n------\n", w);
		ft_printf("neighbor : %d\n", wall->neighborsect);
		ft_printf("picnum : %d\n", wall->middlepicnum);
		ft_printf("texture name = %s\n", wall->texture_name);
		w++;
	}*/
}

void		main_loop(t_data *d)
{
	SDL_Event e;

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
			zoom(d, &e);
		else if (event_mouse_button(d, &e) < 0)
			break ;
		else if (e.type == SDL_MOUSEMOTION)
			event_motion_mouse(d, &e);
		draw_screen(d);
		SDL_FlushEvent(SDL_MOUSEMOTION);
	}
	SDL_DestroyWindow(d->win);
	SDL_Quit();
}

int			main(void)
{
	t_data	d;

	init_data(&d);
	if (init_editor(&d))
		return (EXIT_FAILURE);
	init_sectors(&d);
	main_loop(&d);
	return (EXIT_SUCCESS);
}
