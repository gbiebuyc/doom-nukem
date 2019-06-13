/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:45:28 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/02 19:15:24 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
**	SDL_Delay(300) Ignore esc keypress from closing the game
*/

void		run_game(t_data *d)
{
	pid_t		pid;
	char *const	argv[] = {"doom-nukem", NULL};
	char	**env;

	if (!save_file(d))
	{
		pid = fork();
		if (pid == 0)
			execve(argv[0], argv, env);
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

void		zoom(t_data *d, SDL_Event *e)
{
	if (e->wheel.y > 0)
		d->scale *= (d->scale < 200) ? 1.1 : 1;
	else if (e->wheel.y < 0)
		d->scale *= (d->scale > 10) ? 0.9 : 1;
}

/*
**	interface.mouse_pos used in show_preview (cf. ed_interface_properties2.c)
**	to print the asset preview.
*/

void		event_motion_mouse(t_data *d, SDL_Event *e)
{
	int	x;
	int	y;

	SDL_GetMouseState(&x, &y);
	if (e->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT) || d->sectordrawing)
		(d->interface.select) ? update_wall_pos(d) : 1;
	if (e->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT))
		(d->interface.move) ? update_pos(d, e) : 1;
	if (e->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)
		&& x < W - PROPERTIES_LIMIT &&
		(d->interface.texture_case_select < 0 || x < W - TEXTURE_TOOLBAR))
		update_pos(d, e);
	if (selecting_assets(d, e) != -1)
		d->interface.mouse_pos = (t_vec2f){x, y};
	if (d->interface.show_menu)
		d->interface.is_on_menu = check_if_mouse_on_menu(d, x, y);
	detect_wall(d, e->motion.x, e->motion.y);
	detect_assets(d, e->motion.x, e->motion.y);
}
