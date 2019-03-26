/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 00:16:39 by nallani           #+#    #+#             */
/*   Updated: 2019/03/26 00:30:45 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		reorder_list(void *list, int id)
{
	t_inter inter;
	t_sprite sprite;
	if (id == 1)
	{
		inter = (inter *)list;
		//reorder inter;
	}
	if (id == 2)
	{
		sprite = (sprite *)list;
		//reorder sprite;
	}
}

void		get_inter()
{
 	
}

void		find_intersection(t_args *args)
{
	t_inter		inter;
	t_sprites	sprites;

	
	while (inter)
	{
		draw_column()
			while (inter->sprite)
			{
				draw_sprite(inter->sprite)
				inter->sprite = inter->sprite->next;
			}
	}
}
