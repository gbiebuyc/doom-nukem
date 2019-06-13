/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_interface_open_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 18:10:04 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/13 18:10:05 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"


char	*get_map_to_open(t_data *d, SDL_Event *e)
{
	char	*path;

	path = NULL;
	(void)d;
	(void)e;
	return (path);
}

void		draw_map_list(t_data *d)
{
	int			x;
	int			y;
	t_map_list	*tmp;

	tmp = d->interface.map_list;
	x = 0;
	y = 0;
	while (tmp)
	{
		draw_string(d, (t_font){tmp->filename, x, y += 30, 0x008800, 2});
		tmp = tmp->next;
	}
}

void		free_list(t_data *d)
{
	t_map_list	*tmp;

	while (d->interface.map_list)
	{
		tmp = d->interface.map_list->next;
		free(d->interface.map_list->filename);
		free(d->interface.map_list);
		d->interface.map_list = tmp;
	}
	d->interface.map_list = NULL;
}

void	*new_map_file(t_map_list **file, char *name)
{
	if (!((*file) = (t_map_list*)malloc(sizeof(t_map_list))))
		return (NULL);
	(*file)->filename = ft_strdup(name);
	(*file)->next = NULL;
	return (*file);
}

int			is_validd_map_name(struct dirent *de)
{
	return (de->d_type == DT_REG && de->d_name[0] != '.' &&
			!ft_strcmp(&de->d_name[ft_strlen(de->d_name) - 6], ".DNMAP"));
}

t_map_list	*get_map_list(t_data *d)
{
	DIR				*dr;
	struct dirent	*de;
	t_map_list		*begin;

	free_list(d);
	if (!(dr = opendir(PATH_MAP)))
	{
		d->interface.prompt_map_open = 0;
		ft_printf("Failed to open maps direcory : %s.\n", PATH_MAP);
		return (NULL);
	}
	begin = NULL;
	while ((de = readdir(dr)))
	{
		if (is_validd_map_name(de))
		{
			if (!new_map_file((!d->interface.map_list) ? &d->interface.map_list
							: &d->interface.map_list->next, de->d_name))
				return (NULL);
			begin = (!begin) ? d->interface.map_list : begin;
			if (d->interface.map_list->next)
				d->interface.map_list = d->interface.map_list->next;
		}
	}
	return (begin);
}
