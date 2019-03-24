/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_doom.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 23:02:19 by nallani           #+#    #+#             */
/*   Updated: 2019/03/24 08:41:54 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_DOOM_H
#define STRUCTS_DOOM_H
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

typedef	struct	s_time
{
	struct timeval	tod;
	struct timeval	ini_time;
	// ptet stocker la diff pour utiliser sur un autre event que dans loop ?
}				t_time;

typedef struct	s_data
{
	t_mainWindow	main_win;
	SDL_Event		events;
	t_time			time;
	t_hooks			hooks;
	char			err_count;
}				t_data;

#endif
