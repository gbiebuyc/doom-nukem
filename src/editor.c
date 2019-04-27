/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 01:48:46 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/27 04:18:59 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include <sys/types.h>
#include <sys/wait.h>

#define EDITOR_W 800
#define EDITOR_H 600

void	run_game(char **envp);

int		main(int argc, char **argv, char **envp)
{
	int f;
	t_sector	sectors[MAXNUMSECTORS];
	t_wall		walls[MAXNUMWALLS];

	(void)argc;
	(void)argv;
	sectors[0] = (t_sector){0, 4, 0, 2, 2, 0, 255};
	walls[0] = (t_wall){(t_vec2f){-5, 5}, 0, 0, 0, 0, -1};
	walls[1] = (t_wall){(t_vec2f){ 20, 5}, 0, 1, 0, 0, 1};
	walls[2] = (t_wall){(t_vec2f){ 5,-5}, 0, 2, 0, 0, -1};
	walls[3] = (t_wall){(t_vec2f){-5,-5}, 0, 3, 0, 0, -1};

	sectors[1] = (t_sector){4, 4, 0.5, 1.5, 3, 0, 255};
	walls[4] = (t_wall){(t_vec2f){ 5,-5}, 0, 0, 0, 0, 0};
	walls[5] = (t_wall){(t_vec2f){ 20, 5}, 0, 1, 0, 0, -1};
	walls[6] = (t_wall){(t_vec2f){ 20,-15}, 0, 2, 0, 0, -1};
	walls[7] = (t_wall){(t_vec2f){ 5,-15}, 0, 3, 0, 0, -1};

	int16_t numsectors = 2;
	int16_t numwalls = 8;
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
			write(f, &numsectors, sizeof(numsectors)) < 0 ||
			write(f, sectors, sizeof(*sectors) * numsectors) < 0 ||

			// Write all walls
			write(f, &numwalls, sizeof(numwalls)) < 0 ||
			write(f, walls, sizeof(*walls) * numwalls) < 0
	   )
		printf("error\n");
	close(f);

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
	SDL_Window *win = SDL_CreateWindow("editor", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, EDITOR_W, EDITOR_H, 0);
	SDL_Surface *surface = SDL_GetWindowSurface(win);
	ft_memset(surface->pixels, 0, EDITOR_W * EDITOR_H * 4);
	for (int i = 0; i < numwalls; i++)
	{
		t_vec2f p = walls[i].point;
		p.x = p.x * 5 + EDITOR_W / 2;
		p.y = -p.y * 5 + EDITOR_H / 2;
		((uint32_t*)surface->pixels)[(int)p.x + (int)p.y * EDITOR_W] = 0xffffff;
	}
	SDL_UpdateWindowSurface(win);
	SDL_Event e;
	while (SDL_WaitEvent(&e))
	{
		if (e.type == SDL_QUIT)
			goto exit;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
			goto exit;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r)
			run_game(envp);
	}
exit:
	SDL_DestroyWindow(win);
	SDL_Quit();
}

void	run_game(char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		char *const argv[] = {"doom-nukem", NULL};
		execve(argv[0], argv, envp);
	}
	else
	{
		waitpid(pid, 0, 0);
		// Ignore esc keypress from closing the game
		SDL_Delay(300);
		SDL_FlushEvent(SDL_KEYDOWN);
	}
}
