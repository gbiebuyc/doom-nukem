/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 19:02:13 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/14 19:02:36 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int	read_texture_data(t_data *d, int f)
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

static int	read_textures_name(t_data *d, int f)
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

static int	read_wall_n_sector_data(t_data *d, int f)
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
		return (ft_printf("Failed to read numwwalls.\n"));
	i = -1;
	while (++i < d->numwalls)
		if (read(f, &d->walls[i], sizeof(t_wall)) < 0 ||
			read(f, d->walls[i].texture_name, 100) < 0)
			return (ft_printf("Failed to read wall structure.\n"));
	return (0);
}

int			contain_map_path(char *path)
{
	char	*check;

	check = PATH_MAP;
	if (ft_strncmp(path, &check[2], 5) == 0 ||
		ft_strncmp(path, PATH_MAP, 7) == 0)
		return (1);
	return (0);
}

#define NB_TEX (int[3]){13, 15, 3}
#define NB_PROJECTILE (int[3]){20, 0, 5}

void		load_map(t_data *d, char *map)
{
	int		f;
	char	*map_path;

	map_path = (contain_map_path(map)) ? map : ft_strjoin(PATH_MAP, map);
	if (((f = open(map_path, O_RDONLY)) == -1) ||
		read(f, &d->startcam.pos, sizeof(t_vec3f)) == -1 ||
		read(f, &d->startcam.rot, sizeof(double)) == -1 ||
		read(f, &d->startsectnum, sizeof(int16_t)) == -1)
		exit(ft_printf("Doom : Map error\n"));
	if (read_wall_n_sector_data(d, f) || read_monsters_data(d, f) ||
		read_textures_name(d, f) || read_texture_data(d, f) ||
		read_posters_data(d, f) ||
		load_weapons_texture(d, f, NB_TEX, NB_PROJECTILE) ||
		load_monsters_texture(d, f) || load_sound(d, f))
		exit(1);
	close(f);
	if (!contain_map_path(map))
		free(map_path);
}
