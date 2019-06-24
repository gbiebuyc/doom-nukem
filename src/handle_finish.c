/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_finish.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 20:06:00 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/23 20:42:09 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	clear_sector_sprites(t_data *d, short i)
{
	t_sprite_list	*to_free;
	t_sprite_list	*tmp;

	to_free = d->sectors[i].sprite_list;
	d->sectors[i].sprite_list = NULL;
	while (to_free)
	{
		tmp = to_free->next;
		free(to_free);
		to_free = tmp;
	}
}

void	handle_finish(t_data *d)
{
	int i;

	i = -1;
	while (++i < d->nb_textures)
		SDL_FreeSurface(d->textures[i]);
	i = -1;
	while (++i < MAX_PROJECTILES)
	{
		d->projectiles[i].is_active = false;
	}
	i = -1;
	while (++i < d->numsectors)
		clear_sector_sprites(d, i);
	if (!ft_strlen(d->nextmap))
		the_end(d);
	invoke_msg(d, "YOU FINISHED THE MAP");
	init_everything(d, d->nextmap);
}
