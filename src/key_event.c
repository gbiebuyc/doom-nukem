/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 04:14:37 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 04:16:07 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	event_key_down(t_data *d, SDL_KeyboardEvent event)
{
	if (event.keysym.sym == SDLK_ESCAPE)
		proper_exit(d);
}
