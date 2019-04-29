/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 01:48:46 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/29 22:23:24 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		main(int argc, char **argv)
{
	t_data	d;

	d.scale = 64;
	d.pos = (t_vec2f){-32, -32};
	(void)argc;
	(void)argv;
	init_sdl(&d);
	init_sectors(&d);
	main_loop(&d);
}

void	main_loop(t_data *d)
{
	SDL_Event e;

	(void)d;
	draw_screen(d);
	while (SDL_WaitEvent(&e))
	{
		if (e.type == SDL_QUIT)
			break ;
		else if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
				break ;
			else if (e.key.keysym.sym == SDLK_r)
				run_game();
			else if (e.key.keysym.sym == SDLK_s)
				save_file(d);
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
			create_sector(d);
	}
	SDL_DestroyWindow(d->win);
	SDL_Quit();
}

void	draw_screen(t_data *d)
{
	double scale = W / d->scale;
	ft_memset(d->screen->pixels, 0, W * H * 4);
	for (int i = 0; i < d->numwalls; i++)
	{
		t_vec2f p = d->walls[i].point;
		p.x = p.x * scale - d->pos.x * scale;
		p.y = p.y * scale - d->pos.y * scale;
		((uint32_t*)d->screen->pixels)[(int)p.x + (int)p.y * W] = 0xffffff;
	}
	SDL_UpdateWindowSurface(d->win);
}

void	run_game()
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		char *const argv[] = {"doom-nukem", NULL};
		execve(argv[0], argv, environ);
	}
	else
	{
		waitpid(pid, 0, 0);
		// Ignore esc keypress from closing the game
		SDL_Delay(300);
		SDL_FlushEvent(SDL_KEYDOWN);
	}
}

void	init_sectors(t_data *d)
{
	d->sectors[0] = (t_sector){0, 4, 0, 2, 2, 0, 255};
	d->walls[0] = (t_wall){(t_vec2f){-5, 5}, 0, 0, 0, 0, -1};
	d->walls[1] = (t_wall){(t_vec2f){ 20, 5}, 0, 1, 0, 0, 1};
	d->walls[2] = (t_wall){(t_vec2f){ 5,-5}, 0, 2, 0, 0, -1};
	d->walls[3] = (t_wall){(t_vec2f){-5,-5}, 0, 3, 0, 0, -1};

	d->sectors[1] = (t_sector){4, 4, 0.5, 1.5, 3, 0, 255};
	d->walls[4] = (t_wall){(t_vec2f){ 5,-5}, 0, 0, 0, 0, 0};
	d->walls[5] = (t_wall){(t_vec2f){ 20, 5}, 0, 1, 0, 0, -1};
	d->walls[6] = (t_wall){(t_vec2f){ 20,-15}, 0, 2, 0, 0, -1};
	d->walls[7] = (t_wall){(t_vec2f){ 5,-15}, 0, 3, 0, 0, -1};

	d->numsectors = 2;
	d->numwalls = 8;
}

void	save_file(t_data *d)
{
	int f;

	t_vec3f startpos = {0, 1, 0};
	double angle = 0;
	int16_t startsectnum = 0;

	if (
			((f = open("map01", O_WRONLY | O_CREAT, 0666)) == -1) ||

			// Write starting position
			write(f, &startpos, sizeof(startpos)) < 0 ||
			write(f, &angle, sizeof(angle)) < 0 ||
			write(f, &startsectnum, sizeof(startsectnum)) < 0 ||

			// Write all sectors
			write(f, &d->numsectors, sizeof(d->numsectors)) < 0 ||
			write(f, d->sectors, sizeof(*d->sectors) * d->numsectors) < 0 ||

			// Write all walls
			write(f, &d->numwalls, sizeof(d->numwalls)) < 0 ||
			write(f, d->walls, sizeof(*d->walls) * d->numwalls) < 0
	   )
		printf("error\n");
	else
		printf("saved map01\n");
	close(f);
}

void	create_sector(t_data *d)
{
	(void)d;
}
