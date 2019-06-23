/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_list_manager_assets.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 21:42:38 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/20 21:42:39 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		remove_key_link(t_data *d, t_assets_list *a)
{
	int	w;

	w = -1;
	while (++w < d->numwalls)
		if (d->walls[w].key_num == a->key_num)
			d->walls[w].key_num = 0;
}

static void		fix_list(t_data *d, t_assets_list *prev, t_assets_list *next)
{
	t_assets_list	*lst;

	if (prev)
		lst = prev;
	else
		lst = next;
	while (lst->prev)
		lst = lst->prev;
	lst->begin = lst;
	while (lst->next)
	{
		lst = lst->next;
		lst->begin = lst->prev->begin;
	}
	d->interface.assets_list = lst;
}

int				delete_asset(t_data *d, t_assets_list *lst,
							t_assets_list *prev, t_assets_list *next)
{
	while (lst)
	{
		if (lst->is_select)
		{
			if (lst->is_key)
				remove_key_link(d, lst);
			prev = lst->prev;
			next = lst->next;
			if (prev)
				prev->next = next;
			if (next)
				next->prev = prev;
			free(lst);
			if (!prev && !next)
				d->interface.assets_list = NULL;
			else
				fix_list(d, prev, next);
			d->nb_assets--;
			d->interface.current_selected_asset = NULL;
			return (1);
		}
		lst = lst->prev;
	}
	return (0);
}

t_assets_list	*new_asset(t_vec2f *p, int sectnum, t_assets_list *prev)
{
	t_assets_list	*asset;

	if (!(asset = (t_assets_list*)malloc(sizeof(t_assets_list))))
		return (NULL);
	asset->num_asset = -1;
	asset->is_highlighted = 0;
	asset->is_select = 0;
	asset->sectnunm = sectnum;
	asset->world_pos = *p;
	asset->is_on_floor = true;
	asset->is_on_ceil = false;
	asset->is_interactive = false;
	asset->is_autopick = false;
	asset->collision = false;
	asset->is_jetpack = false;
	asset->is_key = false;
	asset->key_num = 0;
	asset->wall_num = -1;
	asset->stat_mod = (t_stat_modifier){0, 0, 0, 0, 0};
	asset->prev = prev;
	asset->next = NULL;
	return (asset);
}

int				add_assets_to_list(t_data *d, t_vec2f *p, int sectn,
															t_interface *i)
{
	int			selected_asset;

	selected_asset = i->selected_asset;
	if (!i->assets_list)
	{
		if (!(i->assets_list = new_asset(p, sectn, NULL)))
			return (ft_printf("Failed to add asset.\n"));
		i->assets_list->begin = i->assets_list;
		i->assets_list->picnum = selected_asset;
		i->assets_list->num_asset = d->nb_assets + 1;
	}
	else
	{
		if (!(i->assets_list->next = new_asset(p, sectn, i->assets_list)))
			return (ft_printf("Failed to add next asset.\n"));
		i->assets_list->next->begin = i->assets_list->begin;
		i->assets_list->next->picnum = selected_asset;
		i->assets_list->next->num_asset = d->nb_assets + 1;
		i->assets_list = i->assets_list->next;
	}
	d->nb_assets++;
	return (0);
}
