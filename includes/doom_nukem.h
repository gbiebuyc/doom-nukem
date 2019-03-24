/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:53:29 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 07:49:33 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
#define DOOM_NUKEM_H

#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"
#include <time.h> // needed ?
#include <sys/time.h>

#define WIN_WIDTH 800
#define WIN_LENGTH 600
#define CLOCK_PER_SEC 1000000.0

/*
** exit.c
*/

void	proper_exit(t_data *d);

/*
** init_sdl.c
*/

int		ft_init_sdl(t_data *d, int width, int length);

/*
** loop.c
*/

void	loop(t_data *d);

/*
** key_event.c
*/

void	event_key_down(t_data *d, SDL_KeyboardEvent event);

/*
** window_event.c
*/

void	event_window(t_data *d, SDL_WindowEvent event);
#endif
