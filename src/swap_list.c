/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kits <unkown@noaddress.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 20:23:36 by Kits              #+#    #+#             */
/*   Updated: 2019/06/25 21:54:01 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	destroy_mail(short id, t_sector *sector, uint8_t type_to_destroy)
{
	t_sprite_list	*tmp;
	t_sprite_list	*tmp_prev;

	tmp = sector->sprite_list;
	if (!(tmp))
		return ;
	if (tmp->id == id && tmp->type == type_to_destroy)
	{
		sector->sprite_list = tmp->next;
		free(tmp);
		return ;
	}
	tmp_prev = tmp;
	while (tmp)
	{
		if (tmp->id == id && tmp->type == type_to_destroy)
		{
			tmp_prev->next = tmp->next;
			free(tmp);
			return ;
		}
		tmp_prev = tmp;
		tmp = tmp->next;
	}
}

void	swap_list(uint8_t type, uint16_t id, t_data *d, int sectnum[2])
{
	t_sprite_list *tmp[3];

	tmp[0] = d->sectors[sectnum[0]].sprite_list;
	tmp[1] = d->sectors[sectnum[1]].sprite_list;
	tmp[2] = tmp[0];
	if (tmp[0]->type == type && tmp[0]->id == id)
	{
		d->sectors[sectnum[0]].sprite_list = tmp[0]->next;
	}
	else
	{
		while (tmp[0])
		{
			if (tmp[0]->type == type && tmp[0]->id == id)
			{
				tmp[2]->next = tmp[0]->next;
				break ;
			}
			tmp[2] = tmp[0];
			tmp[0] = tmp[0]->next;
		}
	}
	tmp[0]->next = tmp[1];
	d->sectors[sectnum[1]].sprite_list = tmp[0];
}
