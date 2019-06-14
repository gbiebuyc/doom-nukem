/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_interface_map_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 18:10:04 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/13 18:10:05 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	free_list(t_data *d)
{
	t_map_list *tmp;

	while (d->interface.map_list)
	{
		tmp = d->interface.map_list->next;
		free(d->interface.map_list->filename);
		free(d->interface.map_list);
		d->interface.map_list = tmp;
	}
	d->interface.map_list = NULL;
}

static int	is_valid_map_name(struct dirent *de)
{
	return (de->d_type == DT_REG && de->d_name[0] != '.' &&
			!ft_strcmp(&de->d_name[ft_strlen(de->d_name) - 6], ".DNMAP"));
}

static void	*new_map_file(t_map_list **file, char *name, t_map_list *prev)
{
	if (!((*file) = (t_map_list *)malloc(sizeof(t_map_list))))
		return (NULL);
	(*file)->filename = ft_strdup(name);
	(*file)->prev = prev;
	(*file)->next = NULL;
	return (*file);
}

static void	*create_new_link(t_interface *i, struct dirent *de,
													t_map_list *begin)
{
	if (!i->map_list)
	{
		new_map_file(&i->map_list, de->d_name, NULL);
		i->map_list->begin = i->map_list;
	}
	else
	{
		new_map_file(&i->map_list->next, de->d_name, i->map_list);
		i->map_list->next->begin = i->map_list->next->prev->begin;
	}
	if (i->map_list->next)
		i->map_list = i->map_list->next;
	i->nb_map++;
	return ((!begin) ? i->map_list : begin);
}

int			get_map_list(t_data *d)
{
	DIR				*dr;
	struct dirent	*de;
	t_map_list		*begin;

	free_list(d);
	if (!(dr = opendir(PATH_MAP)))
		return (ft_printf("Failed to open maps direcory : %s.\n", PATH_MAP));
	begin = NULL;
	d->interface.nb_map = 0;
	d->interface.map_list_start_i = 0;
	while ((de = readdir(dr)))
		if (is_valid_map_name(de))
			if (!(begin = create_new_link(&d->interface, de, begin)))
				return (ft_printf("Failed to create new link to map_list.\n"));
	d->interface.map_list = begin;
	return (0);
}
