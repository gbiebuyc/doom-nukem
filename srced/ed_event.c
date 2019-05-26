/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:45:28 by mikorale          #+#    #+#             */
/*   Updated: 2019/05/14 23:45:29 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	debug_print(t_data *d)
{
	t_wall		*wall;
	int			w;
	int			s;

	printf("DEBUG OUTPUT:\n");
	w = 0;
	s = 0;
	while (w < d->numwalls)
	{
		if (w == d->sectors[s].firstwallnum)
			printf("sector %d\n", s++);
		wall = d->walls + w;
		printf("wall %d", w);
		if (wall->neighborsect != -1)
			printf(" neighbor %d", wall->neighborsect);
		printf("\n");
		ft_printf("picnum low :%d | mid : %d | up : %d\n", wall->lowerpicnum,
									wall->middlepicnum, wall->upperpicnum);
		ft_printf("texture name = %s\n", wall->texture_name);
		w++;
	}
	printf("\n");
}

/*
**	SDL_Delay(300) Ignore esc keypress from closing the game
*/

static void	run_game(t_data *d)
{
	pid_t		pid;
	char *const	argv[] = {"doom-nukem", NULL};
	extern char	**environ;

	if (!save_file(d))
	{
		pid = fork();
		if (pid == 0)
			execve(argv[0], argv, environ);
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

void		event_keypress(t_data *d, SDL_Keycode key)
{
	if (key == SDLK_ESCAPE)
	{
		d->interface.show_menu = !d->interface.show_menu;
		d->interface.texture_case_select = -1;
	}
	else if (key == SDLK_r || key == SDLK_d)
		(key == SDLK_r) ? run_game(d) : debug_print(d);
	else if (key == SDLK_s)
		(save_file(d)) ? ft_printf("Error during file saving.\n") : 1;
	else if (key == SDLK_l)
		d->grid_locking = !d->grid_locking;
	else if (key == SDLK_SPACE)
		(d->sectordrawing) ? add_wall(d) : add_sector(d);
	else if (key == SDLK_DELETE && !d->sectordrawing)
		del_sector(d, d->selected_sector, (d->sectors + d->selected_sector));
	else if (key == SDLK_KP_1 || key == SDLK_KP_3)
		change_floor_height(d, ((key == SDLK_KP_7) ? -0.1 : 0.1),
													d->selected_sector);
	else if (key == SDLK_KP_7 || key == SDLK_KP_9)
		change_ceil_height(d, ((key == SDLK_KP_7) ? -0.1 : 0.1), d->selected_sector);
	else if (key == SDLK_BACKSPACE)
		cancel_last_wall(d);
}

void		zoom(t_data *d, SDL_Event *e)
{
	if (e->wheel.y > 0)
		d->scale *= (d->scale < 50) ? 1.1 : 1;
	else if (e->wheel.y < 0)
		d->scale *= (d->scale > 10) ? 0.9 : 1;
}

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
		d->interface.mouse_selection_pos = (t_vec2f){x, y};
	if (d->interface.show_menu)
		d->interface.is_on_menu = check_if_mouse_on_menu(d, x, y);
}
