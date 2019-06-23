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

/*
**	properties[6] = assets_options menu
**	properties[19] = sector_options menu
*/

int		is_over_options_menu(t_data *d, int x, int y)
{
	t_btn_option_p	*p;
	t_toolbar		*tb;
	int				endx;

	p = &d->interface.btn_option_p;
	tb = &d->interface.toolbar;
	if (d->interface.prompt_asset_option &&
		x < d->interface.toolbar.properties[6]->w &&
		y > H - d->interface.toolbar.properties[6]->h)
		return (1);
	else if (d->selected_sector >= 0)
	{
		endx = p->sector_options.x;
		if (x > endx && x < endx + tb->properties[19]->w &&
			y > p->sector_options.y && y < H)
			return (2);
	}
	return (0);
}

/*
**	if (button open)
**	else if (save button)
**	else if (exit_button)
*/

int		menu_button(t_data *d, SDL_Event *e)
{
	if (d->interface.show_menu)
	{
		if (e->button.x >= 6 && e->button.x < d->interface.menu->w - 6 &&
			e->button.y >= 6 && e->button.y < 34)
			d->interface.prompt_map_open = (!get_map_list(d)) ? 1 : 0;
		else if (e->button.x >= 6 && e->button.x < d->interface.menu->w - 6 &&
				e->button.y >= 34 && e->button.y < 62)
			save_file(d, d->current_loaded_map);
		else if (e->button.x >= 6 && e->button.x < d->interface.menu->w - 6 &&
				e->button.y >= 62 && e->button.y < d->interface.menu->h - 6)
			return (-1);
	}
	d->interface.show_menu = 0;
	return (1);
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

int		selecting_assets_in_toolbar(t_data *d, SDL_Event *e)
{
	int	y;
	int	i;
	int	limit;

	d->interface.category = -1;
	i = -1;
	limit = 352;
	while (++i < NB_CATEGORY)
	{
		if (i == 1)
			limit = 72;
		y = d->interface.category_pos[i].y;
		if (e->motion.x >= d->interface.category_pos[i].x &&
			e->motion.x <= W - 5 && e->motion.y >= y
			&& e->motion.y <= y + limit)
		{
			d->mouse.x = e->motion.x - d->interface.category_pos[i].x;
			d->mouse.y = e->motion.y - (y + 2);
			d->mouse.x = (int)(d->mouse.x / 38);
			d->mouse.y = (int)(d->mouse.y / 36);
			return (d->interface.category = i);
		}
		limit = 32;
	}
	return (-1);
}
