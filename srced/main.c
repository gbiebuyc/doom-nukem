/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 01:48:46 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/26 12:02:54 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	init_structure(t_data *d)
{
	ft_memset(d, 0, sizeof(t_data));
	d->scale = W / 64;
	d->pos = (t_vec2f){0, 0};
	d->selectedwall = NULL;
	d->selectedwall2 = NULL;
	d->grid_locking = true;
	d->sectordrawing = false;
	d->interface.show_menu = 0;
	d->interface.select = 1;
	d->interface.move = 0;
	d->texture_to_scale = -1;
	d->interface.texture_case_select = -1;
	d->selected_texture = -2;
	d->interface.category = -1;
	d->interface.nb_asset[0] = AMMO_ASSET;
	d->interface.nb_asset[1] = MONSTER_ASSET;
	d->interface.nb_asset[2] = HEAL_ASSET;
	d->interface.nb_asset[3] = 1;
}

void		init_sectors(t_data *d)
{
	d->sectors[0] = (t_sector){0, 4, 0, 1, 0, {0}, 0, 255, "", ""};
	d->walls[0] = (t_wall){(t_vec2f){-2, 2}, 0, 0, 0, 0, -1, ""};
	d->walls[1] = (t_wall){(t_vec2f){ 6, 2}, 0, 0, 0, 0, -1, ""};
	d->walls[2] = (t_wall){(t_vec2f){ 2, -2}, 0, 0, 0, 0, -1, ""};
	d->walls[3] = (t_wall){(t_vec2f){-2, -2}, 0, 0, 0, 0, -1, ""};
	d->numsectors = 1;
	d->numwalls = 4;
}

void		main_loop(t_data *d)
{
	SDL_Event e;

	draw_screen(d);
	while (SDL_WaitEvent(&e))
	{
		if (e.type == SDL_QUIT)
			break ;
		else if (e.type == SDL_KEYDOWN)
			event_keypress(d, e.key.keysym.sym);
		else if (e.type == SDL_MOUSEWHEEL)
			zoom(d, &e);
		else if (event_mouse_button(d, &e) < 0)
			break ;
		else if (e.type == SDL_MOUSEMOTION)
			event_motion_mouse(d, &e);
		draw_screen(d);
		SDL_FlushEvent(SDL_MOUSEMOTION);
	}
	SDL_DestroyWindow(d->win);
	SDL_Quit();
}

int			main(void)
{
	t_data	d;

	init_structure(&d);
	if (init_editor(&d))
		return (EXIT_FAILURE);
	init_sectors(&d);
	main_loop(&d);
	return (EXIT_SUCCESS);
}
