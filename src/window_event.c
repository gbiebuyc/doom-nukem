/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 04:16:13 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 04:16:33 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	event_window(t_data *d, SDL_WindowEvent event)
{
	if (event.event == SDL_WINDOWEVENT_CLOSE)
		proper_exit(d);
}
