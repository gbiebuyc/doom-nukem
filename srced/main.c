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

void	main_loop(t_data *d)
{
	SDL_Event e;

	draw_screen(d);
	while (SDL_WaitEvent(&e))
	{
		if (e.type == SDL_QUIT)
			break ;
		else if (e.type == SDL_KEYDOWN)
			event_keypress(d, &e);
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

int		main()
{
	t_data	d;

	if (init_editor(&d))
		return (EXIT_FAILURE);
	init_sectors(&d);
	main_loop(&d);
	return (EXIT_SUCCESS);
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
	d->sectors[0] = (t_sector){0, 4, 0, 1, 0, {0}, 0, 255};
	d->walls[0] = (t_wall){(t_vec2f){-2, 2}, 0, 0, 0, 0, -1, ""};
	d->walls[1] = (t_wall){(t_vec2f){ 6, 2}, 0, 0, 0, 0, -1, ""};
	d->walls[2] = (t_wall){(t_vec2f){ 2, -2}, 0, 0, 0, 0, -1, ""};
	d->walls[3] = (t_wall){(t_vec2f){-2, -2}, 0, 0, 0, 0, -1, ""};
	d->numsectors = 1;
	d->numwalls = 4;
}

int	write_texture_data(t_data *d, int f)
{
	t_texture_data	*tmp;
	int				i;

	tmp = d->texture_list->begin;
	i = -1;
	while (++i < d->nb_texture)
	{
		if (tmp->used)
		{
			write(f, &d->textures[i]->w, sizeof(int));
			write(f, &d->textures[i]->h, sizeof(int));
			write(f, d->textures[i]->pixels,
				sizeof(int) * (d->textures[i]->w * d->textures[i]->h));
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	reset_used(t_data *d)
{
	t_texture_data *tmp;

	tmp = d->texture_list->begin;
	while (tmp)
	{
		tmp->used = 0;
		tmp = tmp->next;
	}
}

void	set_texture_name(t_data *d, t_sector *s, t_wall *w)
{
	t_texture_data	*tmp;
	int				j;
	int				tex_num;
(void)s;

	tmp = d->texture_list->begin;
	tex_num = 0;
	while (tmp)
	{
	/*	j = -1;
		while (++j < d->numsectors)
			if (s[j].floorpicnum == tex_num || s[j].ceilpicnum == tex_num)
				ft_strcpy(s[j].name, tmp->name);*/
		j = -1;
		while (++j < d->numwalls)
			if (w[j].middlepicnum == tex_num)
				ft_strcpy(w[j].texture_name, tmp->name);
		tex_num++;
		tmp = tmp->next;
	}
}

void	set_texture_used(t_data *d, t_sector *s, t_wall *w)
{
	t_texture_data	*tmp;
	int				j;
	int				tex_num;

	d->nb_used_texture = 0;
	reset_used(d);
	tmp = d->texture_list->begin;
	tex_num = 0;
	while (tmp)
	{
		j = -1;
		while (++j < d->numsectors && tmp->used != 1)
			if (s[j].floorpicnum == tex_num || s[j].ceilpicnum == tex_num)
				d->nb_used_texture +=
					(tmp->used = 1);
		j = -1;
		while (++j < d->numwalls && tmp->used != 1)
			if (w[j].lowerpicnum == tex_num || w[j].middlepicnum == tex_num ||
				w[j].upperpicnum == tex_num)
				d->nb_used_texture +=
					(tmp->used = 1);
		tex_num++;
		tmp = tmp->next;
	}
	set_texture_name(d, s, w);
}

void	save_file(t_data *d)
{
	int f;

	t_vec3f startpos = {0, 0.5, 0};
	double angle = 0;
	int16_t startsectnum = 0;

	if (((f = open("map01", O_WRONLY | O_CREAT, 0666)) == -1) ||
			// starting position
			write(f, &startpos, sizeof(t_vec3f)) < 0 ||
			write(f, &angle, sizeof(double)) < 0 ||
			write(f, &startsectnum, sizeof(int16_t)) < 0 ||

			// Write all sectors
			write(f, &d->numsectors, sizeof(d->numsectors)) < 0 ||
			write(f, d->sectors, sizeof(*d->sectors) * d->numsectors) < 0 ||

			// Write all walls
			write(f, &d->numwalls, sizeof(d->numwalls)) < 0)
	//	/**/write(f, d->walls, sizeof(*d->walls) * d->numwalls) < 0)
		/**/printf("error\n");
	else
	{
		int i = 0;
		// write all walls and the corresponding texture name
		
		set_texture_used(d, d->sectors, d->walls);
		while (i < d->numwalls)
		{
			if (write(f, &d->walls[i], sizeof(t_wall)) < 0 ||
				write(f, d->walls[i].texture_name, 100) < 0)
				exit(ft_printf("error print wall struct\n"));
			i++;
		}
		if (write(f, &d->nb_used_texture, sizeof(int32_t)) < 0)
			ft_printf("Error nb texture write\n");
		t_texture_data	*tmp;
		tmp = d->texture_list->begin;
		while (tmp)
		{
			if (tmp->used)
				if (write(f, tmp->name, 100) < 0)
					exit(ft_printf("failed to write texture_list\n"));
			tmp = tmp->next;
		}
		if (write_texture_data(d, f))
			return ;
		/**/printf("saved map01\n");
	}
	close(f);
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
		ft_printf("picnum low :%d | mid : %d | up : %d\n", wall->lowerpicnum,
									wall->middlepicnum, wall->upperpicnum);
		ft_printf("texture name = %s\n", wall->texture_name);
	}
	printf("\n");
}
