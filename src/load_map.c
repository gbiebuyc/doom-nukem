/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 02:56:31 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/22 02:19:39 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		read_texture_data(t_data *d, int f)
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
		// TODO IF RETURN
		read(f, &w, sizeof(int));
		read(f, &h, sizeof(int));

		d->textures[i] = SDL_CreateRGBSurfaceWithFormat(
			0, w, h, 32, SDL_PIXELFORMAT_ARGB8888);
		if ((read(f, d->textures[i]->pixels, w * h * 4)) < 0)
			return (ft_printf("read tex failed\n"));
	}
	return (0);
}

int		read_textures_name(t_data *d, int f)
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
	if (read_texture_data(d, f))
		return (1);
	return (0);
}

// TODO add sectors reading here

int		read_wall_structure(t_data *d, int f)
{
	int		i;

	i = -1;
	while (++i < d->numwalls)
		if (read(f, &d->walls[i], sizeof(t_wall)) < 0 ||
			read(f, d->walls[i].texture_name, 100) < 0)
			return (ft_printf("failed to read wall structure\n"));
	return (0);
}

void	load_map(t_data *d)
{
	int f;

	if (((f = open("map01", O_RDONLY)) == -1) ||
		// Load starting position
		read(f, &d->cam.pos, sizeof(t_vec3f)) == -1 ||
		read(f, &d->cam.rot, sizeof(double)) == -1 ||
		read(f, &d->cursectnum, sizeof(int16_t)) == -1 ||
		// Load all sectors
		read(f, &d->numsectors, sizeof(int16_t)) == -1 ||
		read(f, d->sectors, sizeof(t_sector) * d->numsectors) == -1 ||
		read(f, &d->numwalls, sizeof(int16_t)) == -1)
	///**/read(f, d->walls, sizeof(*d->walls) * d->numwalls) < 0)
		exit(ft_printf("map error\n"));
	else
	{
		if (read_wall_structure(d, f) || read_textures_name(d, f))
			exit (1);
	}
	close(f);
}
