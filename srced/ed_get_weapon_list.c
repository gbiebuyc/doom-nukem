/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_get_weapon_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 20:59:07 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/16 20:59:07 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		sort_weapon_list(t_data *d, int i, int *nb_tex,
														int *nb_projectile)
{
	int		j;
	int		k;
	char	*tmp;

	j = -1;
	while (++j < nb_tex[i] - 1 && (k = j) > -1)
		while (++k < nb_tex[i])
			if (ft_strcmp(d->weap_list[i][0][j], d->weap_list[i][0][k]) > 0)
			{
				tmp = d->weap_list[i][0][j];
				d->weap_list[i][0][j] = d->weap_list[i][0][k];
				d->weap_list[i][0][k] = tmp;
			}
	j = -1;
	while (++j < nb_projectile[i] - 1 && (k = j) > -1)
		while (++k < nb_projectile[i])
			if (ft_strcmp(d->weap_list[i][1][j], d->weap_list[i][1][k]) > 0)
			{
				tmp = d->weap_list[i][1][j];
				d->weap_list[i][1][j] = d->weap_list[i][1][k];
				d->weap_list[i][1][k] = tmp;
			}
}

static int		read_weapon_projectile(t_data *d, char *path, int *n)
{
	DIR				*dr;
	struct dirent	*de;
	int				i;

	if (!(path = ft_strjoin(path, "/projectiles/")))
		return (ft_printf("strjoin failed lol\n"));
	if (!(dr = opendir(path)))
		return (ft_printf("Failed to open %s\n", path));
	i = 0;
	while (i < n[2] && (de = readdir(dr)))
		if (is_bmp(de))
		{
			if (!(d->weap_list[n[0]][1][i] = ft_strjoin(path, de->d_name)))
				return (ft_printf("strjoin failed lol\n"));
			i++;
		}
	closedir(dr);
	free(path);
	return (0);
}

static int		read_weapon_list(t_data *d, char *weap_name, int *n)
{
	char			*path;
	DIR				*dr;
	struct dirent	*de;
	int				i;

	if (!(path = ft_strjoin(PATH_WEAPONS, weap_name)))
		return (ft_printf("strjoin failed lol\n"));
	if (!(dr = opendir(path)))
		return (ft_printf("Failed to open %s\n", path));
	i = 0;
	while (i < n[1] && (de = readdir(dr)))
		if (is_bmp(de))
		{
			if (!(d->weap_list[n[0]][0][i] = ft_strjoin(path, de->d_name)))
				return (ft_printf("strjoin failed lol\n"));
			i++;
		}
	closedir(dr);
	if (n[2] > 0)
		if (read_weapon_projectile(d, path, n))
			return (1);
	free(path);
	return (0);
}

int				get_weapons_list(t_data *d, char **weap_name, int *nb_tex,
														int *nb_projectile)
{
	int	i;

	i = -1;
	while (++i < 3)
		if (read_weapon_list(d, weap_name[i],
							(int[3]){i, nb_tex[i], nb_projectile[i]}))
			return (1);
	i = -1;
	while (++i < 3)
		sort_weapon_list(d, i, nb_tex, nb_projectile);
	return (0);
}
