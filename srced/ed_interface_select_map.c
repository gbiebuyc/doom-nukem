/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_interface_select_map.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:42:18 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/14 14:42:19 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_rect(t_data *d, int x, int y, int color)
{
	int i;

	i = -1;
	while (++i < 569)
		((uint32_t *)d->screen->pixels)[x + i + y * W] = color;
	i = -1;
	while (++i < 569)
		((uint32_t *)d->screen->pixels)[x + i + (y + 19) * W] = color;
	i = -1;
	while (++i < 19)
		((uint32_t *)d->screen->pixels)[x + (y + i) * W] = color;
	i = -1;
	while (++i < 19)
		((uint32_t *)d->screen->pixels)[x + 569 + (y + i) * W] = color;
}

void		draw_map_list(t_data *d)
{
	int			x;
	int			y;
	t_map_list	*tmp;
	int			cpt;

	draw_string(d, (t_font){"Select a map to open", MAP_PROMPT_X + 105,
											MAP_PROMPT_Y - 20, 0x008800, 2});
	tmp = d->interface.map_list;
	cpt = -1;
	while (++cpt < d->interface.map_list_start_i)
		tmp = tmp->next;
	x = MAP_PROMPT_X + 5;
	y = MAP_PROMPT_Y + 5;
	cpt = -1;
	while (tmp && ++cpt < 10)
	{
		draw_string(d, (t_font){tmp->filename, x, y, 0x008800, 2});
		y += 25;
		tmp = tmp->next;
	}
	x = d->interface.selected_map_pos.x;
	y = d->interface.selected_map_pos.y;
	if (d->interface.selected_map != -1)
		draw_rect(d, x, y, 0xcccc00);
}

void	detect_selected_map(t_data *d, int x, int y)
{
	int select_y;

	d->interface.selected_map = -1;
	if (x > MAP_PROMPT_X && x < MAP_PROMPT_ENDX &&
		y > MAP_PROMPT_Y && y < MAP_PROMPT_ENDY)
	{
		select_y = (y - (MAP_PROMPT_Y)) / 25;
		d->interface.selected_map = select_y + d->interface.map_list_start_i;
		d->interface.selected_map_pos.x = MAP_PROMPT_X + 3;
		d->interface.selected_map_pos.y = MAP_PROMPT_Y + (select_y * 25) + 3;
		if (select_y >= d->interface.nb_map)
			d->interface.selected_map = -1;
	}
}

char	*get_map_to_open(t_data *d, SDL_Event *e)
{
	char	*path;
	int		i;

	path = NULL;
	if (e->button.x >= MAP_PROMPT_X && e->button.x < MAP_PROMPT_ENDX &&
		e->button.y >= MAP_PROMPT_Y && e->button.y <= MAP_PROMPT_ENDY)
	{
		i = -1;
		while (++i < d->interface.selected_map)
			d->interface.map_list = d->interface.map_list->next;
		path = d->interface.map_list->filename;
	}
	return (path);
}
