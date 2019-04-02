/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:10:13 by nallani           #+#    #+#             */
/*   Updated: 2019/04/02 16:48:01 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	button_pressed(t_data *d, SDL_MouseButtonEvent event)
{
	(void)d;
	(void)event;
	return ;
}

void	button_released(t_data *d, SDL_MouseButtonEvent event)
{
	(void)d;
	(void)event;
	return ;
}

void	event_mouse_button(t_data *d, SDL_MouseButtonEvent event)
{
	if (event.state == SDL_PRESSED)
		button_pressed(d, event);
	else
		button_released(d, event);
}
