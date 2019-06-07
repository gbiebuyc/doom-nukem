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

static int	load_texture(t_data *d)
{
	int			i;
	SDL_Surface	*tmp;

	if (!(d->textures =
			(SDL_Surface**)malloc(sizeof(SDL_Surface*) * d->nb_texture)))
		return (ft_printf("Failed to allocate tetures surface memory.\n"));
	i = 0;
	while (i < d->nb_texture)
	{
		if (!(tmp = SDL_LoadBMP(d->texture_list->name)))
			return (ft_printf("Failed to load %s.\n", d->texture_list->name));
		if (!(d->textures[i] = SDL_ConvertSurface(tmp, d->screen->format, 0)))
			return (ft_printf("Failed to re-format\n"));
		if (d->texture_list->next)
			d->texture_list = d->texture_list->next;
		SDL_FreeSurface(tmp);
		i++;
	}
	return (0);
}

static int	new_texture(char *name, t_texture_data **tex_data,
								t_texture_data *begin, t_texture_data *prev)
{
	if (!(*tex_data = (t_texture_data*)malloc(sizeof(t_texture_data))))
		return (1);
	name = ft_strjoin("/", name);
	name = ft_strjoin(TEXTURE_PATH, name);
	ft_strcpy((*tex_data)->name, name);
	(*tex_data)->begin = begin;
	(*tex_data)->prev = prev;
	(*tex_data)->next = NULL;
	return (0);
}

static int	get_texture_files(t_data *d, DIR *dr)
{
	t_texture_data	*list;
	t_texture_data	*save_prev;
	struct dirent	*de;

	list = NULL;
	save_prev = NULL;
	while ((de = readdir(dr)))
	{
		if (de->d_type == DT_REG && de->d_name[0] != '.'
			&& ft_strcmp(&de->d_name[de->d_namlen - 4], ".bmp") == 0)
		{
			if (ft_strequ(de->d_name, "no_texture.bmp"))
				d->default_texture = d->nb_texture;
			if (new_texture(de->d_name, (list) ? &list->next : &d->texture_list,
									(!list) ? NULL : list->begin, save_prev))
				return (ft_printf("Failed to craete new texture.\n"));
			if (!list)
				d->texture_list->begin = d->texture_list;
			list = (!list) ? d->texture_list : list->next;
			save_prev = list;
			d->nb_texture++;
		}
	}
	return (0);
}

int			init_texture(t_data *d)
{
	DIR				*dr;

	d->texture_list = NULL;
	d->nb_texture = 0;
	if ((dr = opendir(TEXTURE_PATH)))
	{
		if (get_texture_files(d, dr) || load_texture(d))
			return (1);
		closedir(dr);
	}
	else
		return (ft_printf("Couldn't open the textures directory.\n"));
	return (0);
}
