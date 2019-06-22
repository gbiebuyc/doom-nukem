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

static int	selecting_wall_or_sector(t_data *d, SDL_Event *e, int x, int y)
{
	if (!is_on_select_move_icon(d, x, y) && d->interface.select &&
		x < W - PROPERTIES_LIMIT && d->interface.texture_case_select < 0
		&& !d->sectordrawing)
	{
		d->selected_sector = find_sect_under_cursor(d);
		select_wall_under_cursor(d, (t_vec2f){e->button.x, e->button.y});
		d->hl_wall = NULL;
		if (d->selected_wall == -1)
			detect_select_wall(d, x, y);
		return (1);
	}
	return (0);
}

static void	mouse_button_left_handler(t_data *d, SDL_Event *e, int x, int y)
{
	SDL_GetMouseState(&x, &y);
	d->interface.current_selected_asset = NULL;
	d->interface.prompt_asset_option = 0;
	if (!select_assets_on_map(d) && !selecting_wall_or_sector(d, e, x, y) &&
		x > W - PROPERTIES_LIMIT)
		btn_height(d, x, y, &d->interface);
	is_on_checkbox(d, x, y, e);
	fix_default_texture(d, x, y);
	if ((d->selected_sector >= 0 || d->selected_wall >= 0 ||
		d->hl_wallnum >= 0) && d->interface.texture_case_select != -1)
		save_selected_texture(d, e->button.x, e->button.y,
			((d->selected_wall != -1) ? d->selected_wall : d->hl_wallnum));
	if (d->selected_texture != -1)
		d->interface.texture_case_select = properties_texture_selection(d, e);
	if (d->interface.category != -1 && !d->interface.btn_right_pressed)
		get_selected_asset(d);
	else if (d->interface.selected_asset != -1 && x < W - PROPERTIES_LIMIT)
		add_asset_to_map(d, x, y);
}

/*
**  The selected walls will be reset only if the click occur inside the map,
**  not if, for example, the click is on the properties menu.
*/

static void	mouse_button_up(t_data *d, SDL_Event *e)
{
	if (d->interface.prompt_map_open)
		return ;
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

static int	mouse_button_down(t_data *d, SDL_Event *e, int x, int y)
{
	if (e->button.button == SDL_BUTTON_LEFT)
	{
		if (d->interface.prompt_map_open)
		{
			if (d->get_next_map)
				get_next_level(d, e);
			else if ((d->map_to_open = get_map_to_open(d, e)))
				return (-2);
		}
		if (menu_button(d, e) == -1)
			return (-1);
		if (!d->interface.prompt_map_open && !d->interface.btn_right_pressed &&
			!is_over_options_menu(d, x, y))
			mouse_button_left_handler(d, e, 0, 0);
		if (is_over_options_menu(d, x, y))
			event_asset_option_handler(d, x, y, &d->interface.btn_option_p);
	}
	if (e->button.button == SDL_BUTTON_RIGHT && !d->interface.prompt_map_open)
	{
		d->interface.select = 0;
		d->interface.btn_right_pressed = 1;
		d->interface.selected_asset = -1;
	}
	return (0);
}

int			event_mouse_button(t_data *d, SDL_Event *e)
{
	int	exit_state;
	int	x;
	int	y;

	SDL_GetMouseState(&x, &y);
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		if ((exit_state = mouse_button_down(d, e, x, y)) < 0)
			return (exit_state);
	}
	else if (e->type == SDL_MOUSEBUTTONUP)
		mouse_button_up(d, e);
	return (0);
}
