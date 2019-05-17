/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 00:28:41 by nallani           #+#    #+#             */
/*   Updated: 2019/05/07 23:19:11 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	load_monster_texture(t_data *d, char *path, int i[3]) //i[0] == monster_id & i[1] == state_of_anim | anim & i[2] == orientation
{
	SDL_Surface *tmp;

	if (!(tmp = SDL_LoadBMP(path)))
		exit(EXIT_FAILURE);
	if (!(d->monster_text[i[0]][i[1]][i[2]] = SDL_ConvertSurfaceFormat(tmp,
					d->screen->format->format, 0)))
		exit(EXIT_FAILURE);
//	printf("%d\n", (int)((int32_t*)d->monster_text[0][0]->pixels)[0]); (wtf color ?)
//	printf("%d\n", (int)((int8_t*)d->monster_text[0][0]->pixels)[0]);
//	printf("%d\n", (int)((int8_t*)d->monster_text[0][0]->pixels)[1]);
//	printf("%d\n", (int)((int8_t*)d->monster_text[0][0]->pixels)[2]);
//	printf("%d\n",(int)((int8_t*)d->monster_text[0][0]->pixels)[3]);
	SDL_FreeSurface(tmp);
}

void	init_sdl(t_data *d)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
		err_exit(d, 0, SDL_GetError());
	if (!(d->win = SDL_CreateWindow("doom-nukem", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0)))
		err_exit(d, 1, SDL_GetError());
	if (!(d->screen = SDL_GetWindowSurface(d->win)))
		err_exit(d, 1, SDL_GetError());
	if (SDL_SetRelativeMouseMode(SDL_TRUE) == -1)
		err_exit(d, 2, SDL_GetError());
	load_monster_texture(d, "./textures/sprites/motherdemon/walk1_idle/MOMDA1.bmp", (int[3]){0, 0, 0});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk1_idle/MOMDA2A8.bmp", (int[3]){0, 0, 1});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk1_idle/MOMDA3A7.bmp", (int[3]){0, 0, 2});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk1_idle/MOMDA4A6.bmp", (int[3]){0, 0, 3});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk1_idle/MOMDA5.bmp", (int[3]){0, 0, 4});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk2/MOMDB1.bmp", (int[3]){0, 1, 0});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk2/MOMDB2B8.bmp", (int[3]){0, 1, 1});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk2/MOMDB3B7.bmp", (int[3]){0, 1, 2});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk2/MOMDB4B6.bmp", (int[3]){0, 1, 3});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk2/MOMDB5.bmp", (int[3]){0, 1, 4});
	d->monster_text[0][2][0] = d->monster_text[0][0][0];
	d->monster_text[0][2][1] = d->monster_text[0][0][1];
	d->monster_text[0][2][2] = d->monster_text[0][0][2];
	d->monster_text[0][2][3] = d->monster_text[0][0][3];
	d->monster_text[0][2][4] = d->monster_text[0][0][4];
	load_monster_texture(d, "./textures/sprites/motherdemon/walk3/MOMDD1.bmp", (int[3]){0, 3, 0});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk3/MOMDD2D8.bmp", (int[3]){0, 3, 1});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk3/MOMDD3D7.bmp", (int[3]){0, 3, 2});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk3/MOMDD4D6.bmp", (int[3]){0, 3, 3});
	load_monster_texture(d, "./textures/sprites/motherdemon/walk3/MOMDD5.bmp", (int[3]){0, 3, 4});

	d->keys = SDL_GetKeyboardState(NULL);

	int fd;
	if (!(fd = open("./gamedata", O_RDONLY)))
		exit(printf("gamedata error\n"));
	struct stat s;
	if (fstat(fd, &s) == -1)
		exit(printf("gamedata error\n"));
	d->gamedata = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	char *p = d->gamedata;
	while (p < (d->gamedata + s.st_size))
	{
		if ((d->gamedata + s.st_size) - p < 512)
			exit(printf("gamedata error\n"));
		int filesize = parseoct(p + 124, 12);
		if (ft_strnequ(p, "map", 3) && filesize > 0)
			load_map(d, p + 512);
		else if (ft_strnequ(p, "tex", 3) && filesize > 0)
			load_tex(d, p + 512);
		p += 512;
		while (filesize > 0)
		{
			filesize -= 512;
			p += 512;
		}
	}
}

void	load_tex(t_data *d, char *p)
{
	t_bitmap *tex = &d->textures[d->numtextures];
	tex->w = *(int32_t*)(p + 18);
	tex->h = *(int32_t*)(p + 22);
	tex->pixels = (uint32_t*)(p + 138);
	d->numtextures++;
}

int		parseoct(const char *p, size_t n)
{
	int i = 0;

	while ((*p < '0' || *p > '7') && n > 0) {
		++p;
		--n;
	}
	while (*p >= '0' && *p <= '7' && n > 0) {
		i *= 8;
		i += *p - '0';
		++p;
		--n;
	}
	return (i);
}
