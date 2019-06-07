/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kits <unkown@noaddress.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 20:23:36 by Kits              #+#    #+#             */
/*   Updated: 2019/06/05 16:30:41 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	swap_list(uint8_t type, uint16_t id, t_data *d, uint16_t cursectnum,
uint16_t new_sect_num)
{
    t_sprite_list *tmp[3];

    tmp[0] = d->sectors[cursectnum].sprite_list;
	tmp[1] = d->sectors[new_sect_num].sprite_list;
	tmp[2] = tmp[0];// windows casse les couilles // inutile d'initialiser ici

	if (tmp[0]->type == type && tmp[0]->id == id)
	{
		d->sectors[cursectnum].sprite_list = tmp[0]->next;
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
	d->sectors[new_sect_num].sprite_list = tmp[0];
}
