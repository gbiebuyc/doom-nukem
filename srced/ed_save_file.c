/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_save_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 13:54:11 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/06 20:37:39 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	write_texture_data(t_data *d, int f)
{
	t_texture_data	*tmp;
	int				i;

	tmp = d->texture_list->begin;
	i = -1;
	while (++i < d->nb_texture)
	{
		if (tmp->used)
		{
			if (write(f, &d->textures[i]->w, sizeof(int)) < 0 ||
				write(f, &d->textures[i]->h, sizeof(int)) < 0 ||
				write(f, d->textures[i]->pixels, 4 * (d->textures[i]->w *
													d->textures[i]->h)) < 0)
				return (ft_printf("Failed to write texture data\n"));
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	write_texture_list(t_data *d, int f)
{
	t_texture_data *tmp;

	if (write(f, &d->nb_used_texture, sizeof(int32_t)) < 0)
		return (ft_printf("Error nb texture write\n"));
	tmp = d->texture_list->begin;
	while (tmp)
	{
		if (tmp->used)
			if (write(f, tmp->name, 100) < 0)
				return (ft_printf("failed to write texture_list\n"));
		tmp = tmp->next;
	}
	return (0);
}

static int	write_wall_n_sector_data(t_data *d, int f)
{
	int i;

	if (write(f, &d->numsectors, sizeof(d->numsectors)) < 0)
		return (ft_printf("Failed to write numsectors.\n"));
	i = -1;
	while (++i < d->numsectors)
		if (write(f, &d->sectors[i], sizeof(t_sector)) < 0 ||
			write(f, d->sectors[i].floor_texture_name, 100) < 0 ||
			write(f, d->sectors[i].ceil_texture_name, 100) < 0)
			return (ft_printf("Failed to write sector structure.\n"));
	if (write(f, &d->numwalls, sizeof(d->numwalls)) < 0)
		return (ft_printf("Failed to write numwwalls."));
	i = -1;
	while (++i < d->numwalls)
		if (write(f, &d->walls[i], sizeof(t_wall)) < 0 ||
			write(f, d->walls[i].texture_name, 100) < 0)
			return (ft_printf("Failed to write wall structure.\n"));
	return (0);
}

int			save_file(t_data *d)
{
	t_vec3f	startpos;
	double	angle;
	int16_t	startsectnum;
	int		f;

	startpos = d->player_start;
	angle = 0;
	startsectnum = d->startsectnum;
	if (((f = open("map01", O_WRONLY | O_CREAT, 0666)) == -1) ||
		write(f, &startpos, sizeof(t_vec3f)) < 0 ||
		write(f, &angle, sizeof(double)) < 0 ||
		write(f, &startsectnum, sizeof(int16_t)) < 0)
		return (ft_printf("Write starting data failed\n"));
	set_texture_used(d, d->sectors, d->walls);
	set_texture_name(d, d->sectors, d->walls);
	if (write_wall_n_sector_data(d, f) || write_monster_data(d, f) ||
		write_texture_list(d, f) || write_texture_data(d, f) ||
		write_monster_texture(d, f, d->texture_monster))
		return (1);
	close(f);
	ft_printf("saved map01\n");
	return (0);
}
