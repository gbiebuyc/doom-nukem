/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_editor_assets_handler2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 21:42:20 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/20 21:42:20 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		check_if_assets_inside_sector(t_data *d)
{
	t_monster_list	*ml;
	t_monster_list	*mtmp;
	t_assets_list	*al;
	t_assets_list	*atmp;

	ml = (d->interface.monster_list) ? d->interface.monster_list->begin : NULL;
	al = (d->interface.assets_list) ? d->interface.assets_list->begin : NULL;
	while (ml)
	{
		mtmp = ml->next;
		if (ml->sectnunm == d->selected_sector && (ml->is_select = 1))
			delete_monster(d, d->interface.monster_list);
		ml = mtmp;
	}
	while (al)
	{
		atmp = al->next;
		if (al->sectnunm == d->selected_sector && (al->is_select = 1))
			delete_asset(d, d->interface.assets_list, NULL, NULL);
		al = atmp;
	}
}

static int	select_monster_on_map(t_data *d)
{
	t_monster_list	*lst;
	int				found;

	found = 0;
	lst = d->interface.monster_list;
	while (lst)
	{
		lst->is_select = 0;
		if (lst->is_highlighted)
		{
			lst->is_select = 1;
			found = 1;
		}
		lst = lst->prev;
	}
	return (found);
}

int			select_assets_on_map(t_data *d)
{
	t_assets_list	*lst;
	int				found;

	if (select_monster_on_map(d))
		return (1);
	found = 0;
	lst = d->interface.assets_list;
	while (lst)
	{
		lst->is_select = 0;
		if (lst->is_highlighted)
		{
			lst->is_select = 1;
			found = 1;
		}
		lst = lst->prev;
	}
	return (found);
}
