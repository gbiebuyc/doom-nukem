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
