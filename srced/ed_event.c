/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:45:28 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/14 18:56:55 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
**	SDL_Delay(300) Ignore esc keypress from closing the game
*/

void		run_game(t_data *d)
{
	pid_t		pid;
	char		name[100];
	char		**argv;
	extern char	**environ;

	if (!save_file(d, d->current_loaded_map))
	{
		ft_strcpy(name, d->path_to_save);
		argv = (char*[]){"doom-nukem", name, NULL};
		pid = fork();
		if (pid == 0)
		{
			if (execve((const char*)argv[0], (char *const *)argv, environ) < 0)
				ft_printf("Failed to start doom.\n");
		}
		else
		{
			waitpid(pid, 0, 0);
			SDL_Delay(300);
			SDL_FlushEvent(SDL_KEYDOWN);
		}
	}
	else
		ft_printf("Error saving file\nAbort running game...\n");
}

void		mouse_wheel(t_data *d, SDL_Event *e)
{
	int	index;

	if (!d->interface.prompt_map_open && e->wheel.y > 0)
		d->scale *= (d->scale < 200) ? 1.1 : 1;
	else if (!d->interface.prompt_map_open && e->wheel.y < 0)
		d->scale *= (d->scale > 10) ? 0.9 : 1;
	if (d->interface.prompt_map_open)
	{
		index = d->interface.map_list_start_i;
		if (e->wheel.y > 0)
			index -= (index > 0) ? 1 : 0;
		if (e->wheel.y < 0)
			index += (index < d->interface.nb_map - 10) ? 1 : 0;
		d->interface.map_list_start_i = index;
	}
}

/*
**	interface.mouse_pos used in show_preview (cf. ed_interface_properties2.c)
**	to print the asset preview.
*/

void		event_motion_mouse(t_data *d, SDL_Event *e, int x, int y)
{
	SDL_GetMouseState(&x, &y);
	if (!d->interface.prompt_map_open)
	{
		if (e->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT) || d->sectordrawing)
			(d->interface.select) ? update_wall_pos(d) : 1;
		if (e->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)
			&& x < W - PROPERTIES_LIMIT && !is_over_options_menu(d, x, y) &&
			(d->interface.texture_case_select < 0 || x < W - TEXTURE_TOOLBAR))
			update_pos(d, e);
		if (selecting_assets_in_toolbar(d, e) != -1)
			d->interface.mouse_pos = (t_vec2){x, y};
		if (d->interface.show_menu)
			d->interface.is_on_menu = check_if_mouse_on_menu(d, x, y);
		if (!is_over_options_menu(d, e->motion.x, e->motion.y))
		{
			detect_wall(d, e->motion.x, e->motion.y);
			detect_assets(d, e->motion.x, e->motion.y);
		}
	}
	else
		detect_selected_map(d, x, y);
}
