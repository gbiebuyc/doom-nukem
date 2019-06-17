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

int		is_bmp(struct dirent *de)
{
	return (de->d_type == DT_REG && de->d_name[0] != '.' &&
			!ft_strcmp(&de->d_name[ft_strlen(de->d_name) - 4], ".bmp"));
}

void	new_asset_data(t_data *d, struct dirent	*de, char *path, int index)
{
	int		i;
	int		j;
	int		k;

	d->assets_data[index].used = 0;
	i = -1;
	j = 0;
	k = 0;
	while (++i < 100)
	{
		if (path[k] && j == 0)
			d->assets_data[index].file[i] = path[k++];
		else
			d->assets_data[index].file[i] =
				(j < (int)ft_strlen(de->d_name)) ? de->d_name[j++] : 0;
	}
	i = -1;
	while (++i < 50)
		d->assets_data[index].name[i] =
			(i < (int)ft_strlen(de->d_name) - 4) ? de->d_name[i] : 0;
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
				if (is_bmp(de) && ++i)
					new_asset_data(d, de, path[n], j++);
			d->interface.nb_asset[n] = i;
			closedir(dr);
		}
		else
			return (ft_printf("Failed to open \"%s\" directory\n", path[n]));
	}
	return (0);
}
