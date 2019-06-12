/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_get_animation_files.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:29:06 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/10 18:29:07 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		get_nb_orientation(char **list, int n)
{
	int		i;
	int		nb;

	i = -1;
	nb = 1;
	while (++i < n)
	{
		if (list[i][0] == list[i + 1][0])
			nb++;
		else
			break ;
	}
	return ((nb == 1) ? 0 : nb);
}

char	**sort(char **list, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (++i < n - 1)
	{
		j = i;
		while (++j < n)
		{
			if (ft_strcmp(list[i], list[j]) > 0)
			{
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
		}
	}
	return (list);
}

char	**load_animation_list(t_data *d, char *path)
{
	DIR				*dr;
	struct dirent	*de;
	int				nb;
	char			**list;
	int				i;

	if (!(dr = opendir(path)) ||
		!(list = (char**)malloc(sizeof(char*) * 50)))
		return (NULL);
	nb = 0;
	while ((de = readdir(dr)))
	{
		if (is_bmp(de) && (i = -1) && nb < 50)
		{
			if (!(list[nb] = (char*)malloc(sizeof(char) * 11)))
				return (NULL);
			while (++i < 10)
				list[nb][i] = (i < (int)ft_strlen(de->d_name)) ?
					de->d_name[i] : 0;
			list[nb][i] = '\0';
			nb++;
		}
	}
	d->nb_anim_tmp = nb;
	d->nb_orientation_tnp = get_nb_orientation(sort(list, nb), nb);
	return (list);
}
