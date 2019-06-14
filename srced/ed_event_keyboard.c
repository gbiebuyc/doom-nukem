/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_event_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:22:53 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/13 16:22:54 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	handle_escape(t_data *d)
{
	if (!d->interface.prompt_map_open)
		d->interface.show_menu = !d->interface.show_menu;
	d->interface.texture_case_select = -1;
	d->interface.selected_asset = -1;
	d->interface.prompt_map_open = 0;
}

void		event_key_up(t_data *d, SDL_Keycode key)
{
	if (key == SDLK_r || key == SDLK_d)
		(key == SDLK_r) ? run_game(d) : debug_print(d);
	else if (key == SDLK_s)
		(save_file(d)) ? ft_printf("Error during file saving.\n") : 1;
	else if (key == SDLK_DELETE && !d->sectordrawing &&
			!delete_monster(d, d->interface.monster_list))
		del_sector(d, d->selected_sector, (d->sectors + d->selected_sector));
	else if (key == SDLK_l)
		d->grid_locking = !d->grid_locking;
	else if (key == SDLK_x)
		d->interface.separate_sector = !d->interface.separate_sector;
	else if (key == SDLK_i && d->selected_sector >= 0)
	{
		d->sectors[d->selected_sector].blinking =
			!d->sectors[d->selected_sector].blinking;
		/**/printf("blinking: %d\n", d->sectors[d->selected_sector].blinking);
	}
}

static void	event_key_down2(t_data *d, SDL_Keycode key)
{
	if (d->selected_sector >= 0 &&
			key == SDLK_KP_2 && d->sectors[d->selected_sector].slope > -90)
	{
		d->sectors[d->selected_sector].slope -= 2;
		ft_printf("slope: %d degree\n", d->sectors[d->selected_sector].slope);
	}
	else if (d->selected_sector >= 0 &&
			key == SDLK_KP_8 && d->sectors[d->selected_sector].slope < 90)
	{
		d->sectors[d->selected_sector].slope += 2;
		ft_printf("slope: %d degree\n", d->sectors[d->selected_sector].slope);
	}
}

void		event_key_down(t_data *d, SDL_Keycode key)
{
	if (key == SDLK_ESCAPE)
		handle_escape(d);
	if (d->interface.prompt_map_open)
		return ;
	if (key == SDLK_SPACE)
		(d->sectordrawing) ? add_wall(d) : add_sector(d);
	else if (key == SDLK_KP_1 || key == SDLK_KP_3)
		floor_height(d, ((key == SDLK_KP_1) ? -0.1 : 0.1), d->selected_sector);
	else if (key == SDLK_KP_7 || key == SDLK_KP_9)
		ceil_height(d, ((key == SDLK_KP_7) ? -0.1 : 0.1), d->selected_sector);
	else if (key == SDLK_BACKSPACE || key == SDLK_g)
		(key == SDLK_BACKSPACE) ? cancel_last_wall(d) : toggle_isdoor(d);
	else if (key == SDLK_b && d->selected_sector >= 0)
		d->sectors[d->selected_sector].outdoor =
			!d->sectors[d->selected_sector].outdoor;
	else if (d->selected_sector >= 0 &&
			((key == SDLK_KP_4 && d->sectors[d->selected_sector].light > 0) ||
			(key == SDLK_KP_6 && d->sectors[d->selected_sector].light < 1)))
		d->sectors[d->selected_sector].light += (key == SDLK_KP_4) ? -0.1 : 0.1;
	else
		event_key_down2(d, key);
}
