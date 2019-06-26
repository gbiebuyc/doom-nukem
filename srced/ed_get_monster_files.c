/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_get_monster_files.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:32:02 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/10 18:32:03 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int					get_monsterdemon_projectile(t_data *d)
{
	DIR				*dr;
	struct dirent	*de;
	char			*path;
	int				i;
	char			*f;

	path = "./textures/assets/monsters/motherdemon/projectiles/";
	if (!(dr = opendir(path)))
		return (ft_printf("Failed to open %s\n", path));
	i = 0;
	while ((de = readdir(dr)))
	{
		if (is_bmp(de))
		{
			if (!(f = ft_strjoin(path, de->d_name)))
				return (ft_printf("strjoin failed\n"));
			if (!(d->projectile_monster[i] = load_bmp(f)))
				return (ft_printf("Failed to load motherdemon projectile\n"));
			i++;
			free(f);
		}
	}
	return (0);
}

static SDL_Surface	**load_anim_tex(t_data *d, char *path, char **list)
{
	SDL_Surface	**anim;
	int			i;
	char		*f;

	if (!(anim = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * d->nb_anim_tmp)))
		return (NULL);
	i = -1;
	while (++i < d->nb_anim_tmp)
	{
		if (!(f = ft_strjoin(path, list[i])) ||
			!(anim[i] = load_bmp(f)))
			return (NULL);
		free(f);
	}
	free(list);
	free(path);
	return (anim);
}

static int			browse_directory(t_data *d, struct dirent *de,
										char *folder, t_monsters_texture *mt)
{
	char	**list;
	char	*path;

	if (de->d_type == DT_DIR && ft_strequ(de->d_name, "walk") &&
		(path = ft_strjoin(folder, "/walk/")))
		if (!(list = load_animation_list(d, path)) ||
			!(mt->walk = load_anim_tex(d, path, list)) ||
			(mt->nb_walk_anim = d->nb_anim_tmp) < 0 ||
			(mt->nb_walk_orientation = d->nb_orientation_tnp) < 0)
			return (ft_printf("Loading walk animation failed.\n"));
	if (de->d_type == DT_DIR && ft_strequ(de->d_name, "attack") &&
		(path = ft_strjoin(folder, "/attack/")))
		if (!(list = load_animation_list(d, path)) ||
			!(mt->attack = load_anim_tex(d, path, list)) ||
			(mt->nb_attack_anim = d->nb_anim_tmp) < 0 ||
			(mt->nb_attack_orientation = d->nb_orientation_tnp) < 0)
			return (ft_printf("Loading attack animation failed.\n"));
	if (de->d_type == DT_DIR && ft_strequ(de->d_name, "death") &&
		(path = ft_strjoin(folder, "/death/")))
		if (!(list = load_animation_list(d, path)) ||
			!(mt->death = load_anim_tex(d, path, list)) ||
			(mt->nb_death_anim = d->nb_anim_tmp) < 0)
			return (ft_printf("Loading death animation failed.\n"));
	return (0);
}

int					get_monsters_files(t_data *d, char *path, int nb_monster)
{
	DIR				*dr;
	struct dirent	*de;
	int				i;
	char			*name;
	char			*folder;

	i = -1;
	while (++i < nb_monster)
	{
		name = d->assets_data[d->interface.nb_asset[0] + i].name;
		if (!(folder = ft_strjoin(path, name)))
			return (ft_printf("Path direcotry malloc failed.\n"));
		if (!(dr = opendir(folder)))
			return (ft_printf("Can't find %s direcotry.\n", folder));
		while ((de = readdir(dr)))
			if (browse_directory(d, de, folder, &d->texture_monster[i]))
				return (1);
		free(folder);
		closedir(dr);
	}
	if (get_monsterdemon_projectile(d))
		return (1);
	return (0);
}
