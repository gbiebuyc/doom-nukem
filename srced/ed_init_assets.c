/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_init_assets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:13:53 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/06 15:13:53 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		get_ground_sprites_files(t_data *d, char *path)
{
	DIR		*dr;

	if ((dr = opendir(path)))
	{
		(void)d; //TODO
	}
	return (0);
}

int		get_weapons_files(t_data *d, char *path)
{
	DIR		*dr;

	if ((dr = opendir(path)))
	{
		(void)d; //TODO
	}
	return (0);
}

int		get_monsters_files(t_data *d, char *path)
{
	DIR		*dr;

	if ((dr = opendir(path)))
	{
		(void)d; //TODO
	}
	return (0);
}

void	new_asset_data(t_data *d, struct dirent	*de, char *path, int index)
{
	char	*tmp;

	d->assets_data[index].file = ft_strjoin("/", de->d_name);
	tmp = d->assets_data[index].file;
	d->assets_data[index].file = ft_strjoin(path, tmp);
	free(tmp);
	d->assets_data[index].used = 0;
	d->assets_data[index].name = ft_strsub(de->d_name, 0, de->d_namlen - 4);
}

int		get_interface_assets_files(t_data *d, char **path)
{
	DIR				*dr;
	struct dirent	*de;
	int				i;
	int				j;
	int				n;

	n = -1;
	j = 0;
	while (++n < 4)
	{
		i = 0;
		if ((dr = opendir(path[n])))
		{
			while ((de = readdir(dr)))
				if (de->d_type == DT_REG && de->d_name[0] != '.' &&
					!ft_strcmp(&de->d_name[de->d_namlen - 4], ".bmp") && ++i)
					new_asset_data(d, de, path[n], j++);
			d->interface.nb_asset[n] = i;
			closedir(dr);
		}
		else
			return (ft_printf("Failed to open \"%s\" directory\n", path[n]));
	}
	return (0);
}
