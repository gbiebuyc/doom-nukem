/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_finish.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 20:06:00 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/18 20:06:00 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	handle_finish(t_data *d)
{
	int i;

	//TODO: Free monster textures
	i = -1;
	while (++i < d->nb_textures)
		SDL_FreeSurface(d->textures[i]);
	init_everything(d, d->nextmap);
}
