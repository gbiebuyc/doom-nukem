/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_event_mouse_button.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 00:22:28 by mikorale          #+#    #+#             */
/*   Updated: 2019/05/18 00:22:30 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	mouse_button_left_handler(t_data *d, SDL_Event *e)
{
	int	x;
	int	y;

	SDL_GetMouseState(&x, &y);
	if (!is_on_select_move_icon(d, x, y) && d->interface.select &&
		x < W - PROPERTIES_LIMIT && d->interface.texture_case_select < 0
		&& !d->sectordrawing)
	{
		d->selected_sector = find_sect_under_cursor(d);
		ft_printf("[Selected sector] = %d\n", d->selected_sector);
		select_wall_under_cursor(d, (t_vec2f){e->button.x, e->button.y});
	}
	else if (x > W - PROPERTIES_LIMIT)
		btn_height(d, x, y, &d->interface);
	if ((d->selected_sector >= 0 || d->selected_wall >= 0)
		&& d->interface.texture_case_select != -1)
		save_selected_texture(d, e->button.x, e->button.y);
	if ((d->selected_sector >= 0 || d->selected_wall >= 0)
		&& d->selected_texture != -1)
		d->interface.texture_case_select = properties_texture_selection(d, e);
}

/*
**  The selected walls will be reset only if the click occur inside the map,
**  not if, for example, the click is on the properties menu.
*/

static void	mouse_button_up(t_data *d, SDL_Event *e)
{
	if (e->button.button == SDL_BUTTON_LEFT && !d->sectordrawing)
	{
		if (!is_on_select_move_icon(d, e->button.x, e->button.y) &&
			e->button.x < W - PROPERTIES_LIMIT &&
			d->interface.texture_case_select < 0)
		{
			d->selectedwall = NULL;
			d->selectedwall2 = NULL;
		}
	}
	else if (e->button.button == SDL_BUTTON_RIGHT)
	{
		d->interface.select = (d->interface.move) ? 0 : 1;
		d->interface.btn_right_pressed = 0;
	}
}

static int	mouse_button_down(t_data *d, SDL_Event *e)
{
	if (menu_save_button(d, e))
		save_file(d);
	else if (menu_exit_button(d, e))
		return (-1);
	d->interface.show_menu = 0;
	if (e->button.button == SDL_BUTTON_LEFT)
		mouse_button_left_handler(d, e);
	if (e->button.button == SDL_BUTTON_RIGHT)
	{
		d->interface.select = 0;
		d->interface.btn_right_pressed = 1;
	}
	return (0);
}

int			event_mouse_button(t_data *d, SDL_Event *e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		if (mouse_button_down(d, e) == -1)
			return (-1);
	}
	else if (e->type == SDL_MOUSEBUTTONUP)
		mouse_button_up(d, e);
	return (0);
}
