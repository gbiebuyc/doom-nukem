/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_save_assets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:55:45 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/09 17:55:46 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	clear_list(t_data *d)
{
	if (!d->monsters)
		return ;
	free(d->monsters);
	d->monsters = NULL;
}

int		fill_monster_structure(t_data *d)
{
	t_monster_list	*lst;
	int				i;

	clear_list(d);
	if (d->nbmonsters <= 0)
		return (0);
	if (!(d->monsters = (t_monster*)malloc(sizeof(t_monster) * d->nbmonsters)))
		return (ft_printf("Failed to malloc monsters structure.\n"));
	lst = d->interface.monster_list->begin;
	i = 0;
	while (lst)
	{
		d->monsters[i] = (t_monster){lst->pos, 1.0, 0.1, 0.0, lst->sectnunm, 0,
									0, 0, 0, 0, 0, 0, 0, 0, 1};
		lst = lst->next;
		i++;
	}
	return (0);
}

int		write_monster_list(t_data *d, int f)
{
	int	i;

	if (write(f, &d->nbmonsters, sizeof(uint16_t)) < 0)
		return (ft_printf("Failed to write nummonsters\n"));
	if (d->nbmonsters > 0)
	{
		fill_monster_structure(d);
		i = -1;
		while (++i < d->nbmonsters)
			 if (write(f, &d->monsters[i], sizeof(t_monster)) < 0)
			 	return (ft_printf("Failed to write monsters\n"));
	}
	return (0);
}
