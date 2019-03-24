/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 23:02:19 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 04:25:52 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H
#include "../SDL/library/include/SDL2/SDL.h"

typedef struct	s_hooks
{
	//insert enums;
}				t_hooks;
typedef struct	s_mainWindow
{
	SDL_Window	*win;
	SDL_Surface	*surface;
}				t_mainWindow;

typedef struct	s_data
{
	t_mainWindow	main_win;
	SDL_Event		events;
	t_hooks			hooks;
}				t_data;

#endif
