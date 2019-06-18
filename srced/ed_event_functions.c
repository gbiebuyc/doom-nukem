/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_event_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:44:59 by mikorale          #+#    #+#             */
/*   Updated: 2019/05/14 23:45:00 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		menu_open_button(t_data *d, SDL_Event *e)
{
	return (d->interface.show_menu &&
			e->button.x >= 6 && e->button.x < d->interface.menu->w - 6 &&
			e->button.y >= 6 && e->button.y < 34 &&
			!(d->interface.show_menu = 0));
}

int		menu_save_button(t_data *d, SDL_Event *e)
{
	return (d->interface.show_menu &&
			e->button.x >= 6 && e->button.x < d->interface.menu->w - 6 &&
			e->button.y >= 34 && e->button.y < 62 &&
			!(d->interface.show_menu = 0));
}

int		menu_exit_button(t_data *d, SDL_Event *e)
{
	return (d->interface.show_menu &&
			e->button.x >= 6 && e->button.x < d->interface.menu->w - 6 &&
			e->button.y >= 62 && e->button.y < d->interface.menu->h - 6 &&
			!(d->interface.show_menu = 0));
}

/*
**	return 	0	for ceil texture seleciton
**			1	for floor texture selection
**			2	for wall texture selection
**	This funciton only tell which case has been clicked on, for further update.
**	0 for the floor texture in sector section
**	1 for the ceil texture
**	2 for the wall texture
*/

int		properties_texture_selection(t_data *d, SDL_Event *e)
{
	int	i;
	int x;
	int	y;

	i = -1;
	while (++i < 4)
	{
		x = (int)d->interface.tex_select[i].x;
		y = (int)d->interface.tex_select[i].y;
		if (e->button.x > x && e->button.x < x + 66 &&
			e->button.y > y && e->button.y < y + 66)
			return (i);
	}
	return (-1);
}

/*
**	limit = size of y axis of each category
*/

int		selecting_assets(t_data *d, SDL_Event *e)
{
	int	y;
	int	i;
	int	limit;

	d->interface.category = -1;
	i = -1;
	while (++i < 4)
	{
		limit = 32;
		if (i == 1)
			limit = 72;
		y = d->interface.category_pos[i].y;
		if (e->motion.x >= W - PROPERTIES_LIMIT && e->motion.y >= y &&
			e->motion.y <= y + limit)
		{
			d->mouse.x = e->motion.x - (W - PROPERTIES_LIMIT + 8);
			d->mouse.y = e->motion.y - (y + 2);
			d->mouse.x = (int)(d->mouse.x / 38);
			d->mouse.y = (int)(d->mouse.y / 36);
			return (d->interface.category = i);
		}
	}
	return (-1);
}
