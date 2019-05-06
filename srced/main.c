/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 01:48:46 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/06 16:56:31 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		main(int argc, char **argv)
{
	t_data	d;

	ft_memset(&d, 0, sizeof(t_data));
	d.scale = W / 64;
	d.pos = (t_vec2f){0, 0};
	d.selectedwall = NULL;
	d.selectedwall2 = NULL;
	d.grid_locking = true;
	d.sectordrawing = false;
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
				run_game(d);
			else if (e.key.keysym.sym == SDLK_s)
				save_file(d);
			else if (e.key.keysym.sym == SDLK_l)
				d->grid_locking = !d->grid_locking;
			else if (e.key.keysym.sym == SDLK_SPACE)
			{
				if (d->sectordrawing)
					add_wall(d);
				else
					add_sector(d);
			}
			else if (e.key.keysym.sym == SDLK_d)
				debug_print(d);
			else if (e.key.keysym.sym == SDLK_DELETE)
				del_sector(d, find_sect_under_cursor(d));
			else if (e.key.keysym.sym == SDLK_PAGEDOWN)
				change_floor_height(d, -0.1, find_sect_under_cursor(d));
			else if (e.key.keysym.sym == SDLK_PAGEUP)
				change_floor_height(d, +0.1, find_sect_under_cursor(d));
			else if (e.key.keysym.sym == SDLK_BACKSPACE)
				cancel_last_wall(d);
		}
		else if (e.type == SDL_MOUSEWHEEL) // Zoom
			d->scale *= (e.wheel.y > 0) ? 1.1 : 0.9;
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
				select_wall_under_cursor(d, (t_vec2f){e.button.x, e.button.y});
			else if (e.button.button == SDL_BUTTON_RIGHT)
				update_pos(d);
		}
		else if (e.type == SDL_MOUSEBUTTONUP)
		{
			if (e.button.button == SDL_BUTTON_LEFT && !d->sectordrawing)
			{
				d->selectedwall = NULL;
				d->selectedwall2 = NULL;
			}
		}
		else if (e.type == SDL_MOUSEMOTION)
		{
			if (e.motion.state & SDL_BUTTON(SDL_BUTTON_LEFT) || d->sectordrawing)
				update_wall_pos(d);
			if (e.motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT))
				update_pos(d);
		}
		draw_screen(d);
		SDL_FlushEvent(SDL_MOUSEMOTION);
	}
	SDL_DestroyWindow(d->win);
	SDL_Quit();
}

void	run_game(t_data *d)
{
	pid_t	pid;

	save_file(d);
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
	d->sectors[0] = (t_sector){0, 4, 0, 1, 2, 0, 255};
	d->walls[0] = (t_wall){(t_vec2f){-2, 2}, 0, 0, 0, 0, -1};
	d->walls[1] = (t_wall){(t_vec2f){ 6, 2}, 0, 1, 0, 0, 1};
	d->walls[2] = (t_wall){(t_vec2f){ 2,-2}, 0, 2, 0, 0, -1};
	d->walls[3] = (t_wall){(t_vec2f){-2,-2}, 0, 3, 0, 0, -1};

	d->sectors[1] = (t_sector){4, 4, 0.1, 0.9, 3, 0, 255};
	d->walls[4] = (t_wall){(t_vec2f){ 2,-2}, 0, 0, 0, 0, 0};
	d->walls[5] = (t_wall){(t_vec2f){ 6, 2}, 0, 1, 0, 0, -1};
	d->walls[6] = (t_wall){(t_vec2f){ 6,-6}, 0, 2, 0, 0, -1};
	d->walls[7] = (t_wall){(t_vec2f){ 2,-6}, 0, 3, 0, 0, -1};

	d->numsectors = 2;
	d->numwalls = 8;
}

void	save_file(t_data *d)
{
	int f;

	t_vec3f startpos = {0, 0.5, 0};
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

void	add_sector(t_data *d)
{
	d->sectordrawing = true;
	d->numsectors++;
	d->sectors[d->numsectors - 1].firstwallnum = d->numwalls;
	d->sectors[d->numsectors - 1].numwalls = 0;
	d->sectors[d->numsectors - 1].floorheight = 0;
	d->sectors[d->numsectors - 1].ceilheight = 1;
	d->sectors[d->numsectors - 1].floorpicnum = 1;
	add_wall(d); // First wall
	add_wall(d); // Current wall
}

void	add_wall(t_data *d)
{
	t_wall	*wall;
	int		x, y;

	t_sector *sect = &d->sectors[d->numsectors - 1];
	if (sect->numwalls >= 2)
	{
		wall = d->walls + sect->firstwallnum;
		if (same_pos(wall, d->selectedwall))
		{
			// The loop is done when you press the
			// space bar at the first point again.
			d->numwalls--;
			sect->numwalls--;
			d->sectordrawing = false;
			return ;
		}
	}
	for (int i = 0; i < sect->numwalls - 1; i++)
	{
		// Check if there is not already a wall at this point.
		wall = d->walls + sect->firstwallnum + i;
		if (same_pos(wall, d->selectedwall))
			return ;
	}
	d->numwalls++;
	sect->numwalls++;
	SDL_GetMouseState(&x, &y);
	t_vec2f p = grid_lock(d, screentoworld(d, (t_vec2f){x, y}));
	d->walls[d->numwalls - 1].point = p;
	d->walls[d->numwalls - 1].neighborsect = -1;
	d->selectedwall = &d->walls[d->numwalls - 1];
}

bool	same_pos(t_wall *w0, t_wall *w1)
{
	return (w0->point.x == w1->point.x &&
			w0->point.y == w1->point.y);
}

void	detect_neighbors(t_data *d, int16_t sectnum)
{
	int npoints = d->sectors[sectnum].numwalls;
	if (npoints < 2)
		return ;
	for (int i = npoints-1, j = 0; j < npoints; i = j++)
	{
		t_wall *w0 = &d->walls[d->sectors[sectnum].firstwallnum + i];
		t_wall *w1 = &d->walls[d->sectors[sectnum].firstwallnum + j];
		w0->neighborsect = -1;
		for (int s = 0; s < d->numsectors && w0->neighborsect == -1; s++)
		{
			if (s == sectnum)
				continue ;
			for (int k = d->sectors[s].numwalls - 1, l = 0;
					l < d->sectors[s].numwalls; k = l++)
			{
				t_wall *w2 = &d->walls[d->sectors[s].firstwallnum + k];
				t_wall *w3 = &d->walls[d->sectors[s].firstwallnum + l];
				if (same_pos(w0, w3) && same_pos(w1, w2))
				{
					w0->neighborsect = s;
					w2->neighborsect = sectnum;
					break ;
				}
			}
		}
	}
}

void	select_wall_under_cursor(t_data *d, t_vec2f p)
{
	double min_dist = INFINITY;
	d->selectedwall = NULL;
	d->selectedwall2 = NULL;
	t_wall *wall = d->walls;
	while (wall - d->walls < d->numwalls)
	{
		// Find closest wall. Priority to walls that have a neighbor.
		t_vec2f p2 = worldtoscreen(d, wall->point);
		double dist = vec2f_length((t_vec2f){p.x - p2.x, p.y - p2.y});
		if (dist < 50 && ((dist < min_dist) ||
					(dist == min_dist && wall->neighborsect != -1)))
		{
			d->selectedwall = wall;
			min_dist = dist;
		}
		wall++;
	}
	if (d->selectedwall && d->selectedwall->neighborsect != -1)
	{
		// Find corresponding neighbor wall.
		t_sector *neighborsect = &d->sectors[d->selectedwall->neighborsect];
		for (int i = 0; i < neighborsect->numwalls; i++)
		{
			wall = d->walls + neighborsect->firstwallnum + i;
			if (same_pos(wall, d->selectedwall))
			{
				d->selectedwall2 = wall;
				break ;
			}
		}
	}
	update_wall_pos(d);
}

void	update_wall_pos(t_data *d)
{
	int		x, y;

	if (!d->selectedwall)
		return ;
	SDL_GetMouseState(&x, &y);
	t_vec2f p = grid_lock(d, screentoworld(d, (t_vec2f){x, y}));
	d->selectedwall->point = p;
	if (d->selectedwall2)
		d->selectedwall2->point = p;
	else
		detect_neighbors(d, in_which_sector_is_this_wall(d, d->selectedwall));
}

void	update_pos(t_data *d)
{
	int		x, y;

	SDL_GetMouseState(&x, &y);
	d->pos = screentoworld(d, (t_vec2f){x, y});
	SDL_WarpMouseInWindow(d->win, W / 2, H / 2);
}

int16_t	in_which_sector_is_this_wall(t_data *d, t_wall *wall)
{
	int s, w;

	for (s = 0, w = wall - d->walls; s < d->numsectors; s++)
		if (d->sectors[s].firstwallnum > w)
			break ;
	return (s - 1);
}

void	debug_print(t_data *d)
{
	t_wall		*wall;

	printf("DEBUG OUTPUT:\n");
	for (int w = 0, s = 0; w < d->numwalls; w++)
	{
		if (w == d->sectors[s].firstwallnum)
			printf("sector %d\n", s++);
		wall = d->walls + w;
		printf("wall %d", w);
		if (wall->neighborsect != -1)
			printf(" neighbor %d", wall->neighborsect);
		printf("\n");
	}
	printf("\n");
}

void	del_sector(t_data *d, int16_t sectnum)
{
	if (sectnum < 0)
		return ;
	t_sector *sect = d->sectors + sectnum;
	int n = sect->numwalls;
	d->numwalls -= n;
	for (int w = sect->firstwallnum; w < d->numwalls; w++)
	{
		d->walls[w] = d->walls[w + n];
		if (d->walls[w].neighborsect == sectnum)
			d->walls[w].neighborsect = -1;
		if (d->walls[w].neighborsect > sectnum)
			d->walls[w].neighborsect--;
	}
	d->numsectors--;
	for (int s = sectnum; s < d->numsectors; s++)
	{
		d->sectors[s] = d->sectors[s + 1];
		d->sectors[s].firstwallnum -= n;
	}
}

int16_t	find_sect_under_cursor(t_data *d)
{
	int		x, y;

	SDL_GetMouseState(&x, &y);
	t_vec2f p = screentoworld(d, (t_vec2f){x, y});
	for (int s = 0; s < d->numsectors; s++)
		if (inside(d, s, p))
			return (s);
	return (-1);
}

bool	inside(t_data *d, int16_t sectnum, t_vec2f test)
{
	int i, j;
	bool c = 0;

	int npoints = d->sectors[sectnum].numwalls;
	for (i = 0, j = npoints-1; i < npoints; j = i++)
	{
		t_vec2f p0 = d->walls[d->sectors[sectnum].firstwallnum + i].point;
		t_vec2f p1 = d->walls[d->sectors[sectnum].firstwallnum + j].point;
		if ( ((p0.y > test.y) != (p1.y > test.y)) &&
				(test.x < (p1.x-p0.x) * (test.y-p0.y) / (p1.y-p0.y) + p0.x) )
			c = !c;
	}
	return (c);
}

void	change_floor_height(t_data *d, double val, int16_t sectnum)
{
	if (sectnum < 0)
		return ;
	d->sectors[sectnum].floorheight += val;
	printf("sect %d floorheight = %f\n", sectnum, d->sectors[sectnum].floorheight);
}

void	cancel_last_wall(t_data *d)
{
	if (!d->sectordrawing)
		return ;
	t_sector *sect = &d->sectors[d->numsectors - 1];
	sect->numwalls--;
	d->numwalls--;
	if (sect->numwalls >= 2)
	{
		d->selectedwall--;
		update_wall_pos(d);
	}
	else
	{
		d->numwalls--;
		d->numsectors--;
		d->selectedwall = NULL;
		d->sectordrawing = false;
	}
}
