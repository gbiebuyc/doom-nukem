/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_init_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:32:57 by mikorale          #+#    #+#             */
/*   Updated: 2019/05/15 19:32:58 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	load_texture(t_data *d, SDL_Surface ***s, int nb_tex,
													t_texture_data *tex_list)
{
	int			i;
	SDL_Surface	*tmp;

	if (!((*s) = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * nb_tex)))
		return (ft_printf("Failed to allocate tetures surface memory.\n"));
	i = 0;
	while (i < nb_tex)
	{
		if (!(tmp = SDL_LoadBMP(tex_list->name)))
			return (ft_printf("Failed to load %s.\n", tex_list->name));
		if (!((*s)[i] = SDL_ConvertSurfaceFormat(tmp,
											SDL_PIXELFORMAT_ARGB8888, 0)))
			return (ft_printf("Failed to re-format\n"));
		if (tex_list->next)
			tex_list = tex_list->next;
		SDL_FreeSurface(tmp);
		i++;
	}
	(void)d;
	return (0);
}

static int	new_texture(char *name, t_texture_data **tex_data,
								t_texture_data *begin, char *path)
{
	if (!(*tex_data = (t_texture_data*)malloc(sizeof(t_texture_data))))
		return (1);
	name = ft_strjoin(path, name);
	ft_strcpy((*tex_data)->name, name);
	(*tex_data)->begin = begin;
	(*tex_data)->next = NULL;
	return (0);
}

static int	get_texture_files(t_data *d, DIR *dr, t_texture_data **tex_lst,
																int *nb_tex)
{
	t_texture_data	*list;
	struct dirent	*de;

	list = NULL;
	while ((de = readdir(dr)))
	{
		if (is_bmp(de))
		{
			if (ft_strequ(de->d_name, "no_texture.bmp"))
				d->default_texture = *nb_tex;
			if (new_texture(de->d_name, (list) ? &list->next : tex_lst,
									(!list) ? NULL : list->begin, d->path))
				return (ft_printf("Failed to craete new texture.\n"));
			if (!list)
				(*tex_lst)->begin = *tex_lst;
			list = (!list) ? *tex_lst : list->next;
			(*nb_tex)++;
		}
	}
	if (*nb_tex == 0)
		return (ft_printf("Textures folder is empty, no texture to load.\n"));
	return (0);
}

int			init_texture(t_data *d)
{
	DIR				*dr;

	d->path = TEXTURE_PATH;
	if ((dr = opendir(d->path)))
		if (get_texture_files(d, dr, &d->texture_list, &d->nb_texture) ||
			load_texture(d, &d->textures, d->nb_texture, d->texture_list))
			return (1);
	if (!dr)
		return (ft_printf("Couldn't open the %s.\n", d->path));
	closedir(dr);
	d->path = POSTERS_PATH;
	if ((dr = opendir(d->path)))
		if (get_texture_files(d, dr, &d->posters_list, &d->nb_posters) ||
			load_texture(d, &d->posters, d->nb_posters, d->posters_list))
			return (1);
	if (!dr)
		return (ft_printf("Couldn't open the %s.\n", d->path));
	closedir(dr);
	d->default_wall_texture = d->default_texture;
	d->default_floor_texture = d->default_texture;
	d->default_ceil_texture = d->default_texture;
	return (0);
}
