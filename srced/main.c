/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 01:48:46 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/30 11:23:31 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		main(int argc, char **argv)
{
	t_data	d;

	d.scale = W / 64;
	d.pos = (t_vec2f){0, 0};
	(void)argc;
	(void)argv;
	init_sdl(&d);
	init_sectors(&d);
	main_loop(&d);
}

void	main_loop(t_data *d)
{
	SDL_Event e;

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
		else if (e.type == SDL_MOUSEWHEEL) // Zoom
			d->scale *= (e.wheel.y == 1) ? 1.1 : 0.9;
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				t_vec2f p = screentoworld(d, (t_vec2f){e.button.x, e.button.y});
				printf("%f, %f\n", p.x, p.y);
				// Create wall at this point
			}
			else if (e.button.button == SDL_BUTTON_RIGHT)
				SDL_WarpMouseInWindow(d->win, W / 2, H / 2);
		}
		else if (e.type == SDL_MOUSEMOTION &&
				(e.motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)))
		{
			// Drag the view / pos
			d->pos = screentoworld(d, (t_vec2f){e.motion.x, e.motion.y});
			SDL_WarpMouseInWindow(d->win, W / 2, H / 2);
		}
		draw_screen(d);
		SDL_FlushEvent(SDL_MOUSEMOTION);
	}
	SDL_DestroyWindow(d->win);
	SDL_Quit();
}

void	draw_screen(t_data *d)
{
	ft_memset(d->screen->pixels, 0, W * H * 4);
	draw_grid(d);
	for (int s = 0; s < d->numsectors; s++)
		draw_sector(d, s);
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

void	draw_grid(t_data *d)
{
	int x;
	int y;

	for (int i = -GRIDSIZE; i <= GRIDSIZE; i++)
	{
		x = worldtoscreen(d, (t_vec2f){i, 0}).x;
		for (y = 0; y < H; y++)
			putpixel(d, x, y, 0x505050);
		y = worldtoscreen(d, (t_vec2f){0, i}).y;
		for (x = 0; x < W; x++)
			putpixel(d, x, y, 0x505050);
	}
}

void	draw_line(t_data *d, t_vec2f v1, t_vec2f v2, uint32_t color)
{
	t_vec2	delta;
	int		steps;
	t_vec2f	increment;

	delta.x = v2.x - v1.x;
	delta.y = v2.y - v1.y;
	steps = (abs(delta.x) > abs(delta.y)) ? abs(delta.x) : abs(delta.y);
	increment.x = delta.x / (double)steps;
	increment.y = delta.y / (double)steps;
	while (steps--)
	{
		putpixel(d, (int)v1.x, (int)v1.y, color);
		v1 = add_vec2f(v1, increment);
	}
}

void	draw_sector(t_data *d, int16_t sectnum)
{
	int i, j;

	int npoints = d->sectors[sectnum].numwalls;
	for (i = 0, j = npoints-1; i < npoints; j = i++)
	{
		t_vec2f p0 = d->walls[d->sectors[sectnum].firstwallnum + i].point;
		t_vec2f p1 = d->walls[d->sectors[sectnum].firstwallnum + j].point;
		p0 = worldtoscreen(d, p0);
		p1 = worldtoscreen(d, p1);
		draw_line(d, p0, p1, 0xffffff);
	}
}

t_vec2f	worldtoscreen(t_data *d, t_vec2f p)
{
	return ((t_vec2f){(p.x - d->pos.x) * d->scale + W / 2,
			-(p.y - d->pos.y) * d->scale + H / 2});
}

t_vec2f	screentoworld(t_data *d, t_vec2f p)
{
	return ((t_vec2f){(p.x - W / 2) / d->scale + d->pos.x,
			-(p.y - H / 2) / d->scale + d->pos.y});
}