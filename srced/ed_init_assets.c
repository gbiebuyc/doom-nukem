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

static void	tmp_fix(t_data *d)
{
	int		i;
	char 	**name;

	name = (char*[]){"motherdemon", "chargingdemon"};
	i = -1;
	while (++i < 11)
		d->assets_data[d->interface.nb_asset[0]].name[i] = name[0][i];
	d->assets_data[d->interface.nb_asset[0]].name[i] = '\0';
	i = -1;
	while (++i < 13)
		d->assets_data[d->interface.nb_asset[0] + 1].name[i] = name[1][i];
	d->assets_data[d->interface.nb_asset[0] + 1].name[i] = '\0';
}

static void	sort_assets(t_data *d)
{
	int				i;
	int				j;
	t_assets_data	tmp;

	i = -1;
	while (++i < d->interface.nb_asset[0] - 1)
	{
		j = i;
		while (++j < d->interface.nb_asset[0])
		{
			if (ft_strcmp(d->assets_data[j].name, d->assets_data[i].name) < 0)
			{
				tmp = d->assets_data[i];
				d->assets_data[i] = d->assets_data[j];
				d->assets_data[j] = tmp;
			}
		}
	}
}

int			is_bmp(struct dirent *de)
{
	return (de->d_type == DT_REG && de->d_name[0] != '.' &&
			!ft_strcmp(&de->d_name[ft_strlen(de->d_name) - 4], ".bmp"));
}

void		new_asset_data(t_data *d, struct dirent	*de, char *path, int index)
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

int			get_interface_assets_files(t_data *d, char **path)
{
	DIR				*dr;
	struct dirent	*de;
	int				i;
	int				j;
	int				n;

	n = -1;
	j = 0;
	while (++n < NB_CATEGORY)
	{
		i = 0;
		if ((dr = opendir(path[n])))
		{
			while ((de = readdir(dr)) && j < MAX_ASSETS)
				if (is_bmp(de) && ++i)
					new_asset_data(d, de, path[n], j++);
			d->interface.nb_asset[n] = i;
			closedir(dr);
		}
		else
			return (ft_printf("Failed to open \"%s\" directory\n", path[n]));
	}
	tmp_fix(d);
	sort_assets(d);
	return (0);
}
