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
	int x;
	int	y;

	x = (int)d->interface.tex_select[0].x;
	y = (int)d->interface.tex_select[0].y;
	if (e->button.x > x && e->button.x < x + 66 &&
		e->button.y > y && e->button.y < y + 66)
		return (0);
	x = (int)d->interface.tex_select[1].x;
	y = (int)d->interface.tex_select[1].y;
	if (e->button.x > x && e->button.x < x + 66 &&
		e->button.y > y && e->button.y < y + 66)
		return (1);
	x = (int)d->interface.tex_select[2].x;
	y = (int)d->interface.tex_select[2].y;
	if (e->button.x > x && e->button.x < x + 66 &&
		e->button.y > y && e->button.y < y + 66)
		return (2);
	return (-1);
}

int		selecting_assets(t_data *d, SDL_Event *e)
{
	int	y;
	int	i;
	int	limit;

	i = -1;
	limit = 137;
	d->interface.category = -1;
	while (++i < 4)
	{
		y = d->interface.category_pos[i].y;
		if (e->motion.x >= W - PROPERTIES_LIMIT && e->motion.y >= y &&
			e->motion.y <= y + limit)
		{
			d->temp.x = e->motion.x - (W - PROPERTIES_LIMIT + 8);
			d->temp.y = e->motion.y - (y + 2);
			d->temp.x = (int)(d->temp.x / 38);
			d->temp.y = (int)(d->temp.y / 36);
			return (d->interface.category = i);
		}
		if (i == 1)
			limit = 32;
	}
	return (-1);
}
