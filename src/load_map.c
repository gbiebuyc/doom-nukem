/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 02:56:31 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/06 20:11:00 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int		read_texture_data(t_data *d, int f)
{
	int	i;
	int w;
	int h;

	if (!(d->textures =
		(SDL_Surface**)malloc(sizeof(SDL_Surface*) * d->nb_textures)))
		return (ft_printf("malloc fail"));
	i = -1;
	while (++i < d->nb_textures)
	{
		if (read(f, &w, sizeof(int)) < 0 || read(f, &h, sizeof(int)) < 0)
			return (ft_printf("Failed to read texture size\n"));
		if (!(d->textures[i] = SDL_CreateRGBSurfaceWithFormat(
			0, w, h, 32, SDL_PIXELFORMAT_ARGB8888)))
			return (ft_printf("Failed to allocate texture surface\n"));
		if ((read(f, d->textures[i]->pixels, w * h * 4)) < 0)
			return (ft_printf("Read texture data failed\n"));
	}
	return (0);
}

static int		read_textures_name(t_data *d, int f)
{
	int		i;

	if (read(f, &d->nb_textures, sizeof(int32_t)) < 0)
		return (ft_printf("Failed read nb_teture\n"));
	if (!(d->tex_name_list = (char**)malloc(sizeof(char*) * d->nb_textures)))
		return (ft_printf("failed to malloc tex name list\n"));
	i = -1;
	while (++i < d->nb_textures)
	{
		if (!(d->tex_name_list[i] = (char*)malloc(sizeof(char) * 100)))
			return (ft_printf("failed to malloc tex\n"));
		if (read(f, d->tex_name_list[i], 100) < 0)
			return (ft_printf("failed to read tex name"));
	}
	return (0);
}

/*
**	Read the number of sectors and walls
**	And get all the data structure
*/

static int		read_wall_n_sector_data(t_data *d, int f)
{
	int		i;

	if (read(f, &d->numsectors, sizeof(int16_t)) < 0)
		return (ft_printf("Failed to read numsectors.\n"));
	i = -1;
	while (++i < d->numsectors)
		if (read(f, &d->sectors[i], sizeof(t_sector)) < 0 ||
			read(f, d->sectors[i].floor_texture_name, 100) < 0 ||
			read(f, d->sectors[i].ceil_texture_name, 100) < 0)
			return (ft_printf("Failed to read sector structure.\n"));
	if (read(f, &d->numwalls, sizeof(int16_t)) < 0)
		return (ft_printf("Faield to read numwwalls.\n"));
	i = -1;
	while (++i < d->numwalls)
		if (read(f, &d->walls[i], sizeof(t_wall)) < 0 ||
			read(f, d->walls[i].texture_name, 100) < 0)
			return (ft_printf("Failed to read wall structure.\n"));
	return (0);
}

void	load_map(t_data *d)
{
	int f;
// nap_path in argv[1]
	if (((f = open("map01.DNMAP", O_RDONLY)) == -1) ||
		read(f, &d->cam.pos, sizeof(t_vec3f)) == -1 ||
		read(f, &d->cam.rot, sizeof(double)) == -1 ||
		read(f, &d->cursectnum, sizeof(int16_t)) == -1)
		exit(ft_printf("map error\n"));
	if (read_wall_n_sector_data(d, f) || read_monsters_data(d, f) ||
		read_textures_name(d, f) || read_texture_data(d, f))
		exit (1);
	/********** */
	if (load_monsters_texture(d, f))
		exit(1);
	/********** */
	close(f);
}
