/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_doom.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 23:02:19 by nallani           #+#    #+#             */
/*   Updated: 2019/04/02 15:27:21 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_DOOM_H
#define STRUCTS_DOOM_H
#include "../SDL/library/include/SDL2/SDL.h"

typedef struct	s_vec3f
{
	double		x;
	double		y;
	double		z;
}				t_vec3f;

typedef struct	s_vec2f
{
	double		x;
	double		y;
}				t_vec2f;

typedef struct	s_hooks
{
	//insert enums;
}				t_hooks;

typedef struct	s_player
{
	t_vec3f		pos;
	t_vec2f		dir;
	t_vec2f		plane;
}				t_player;

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

typedef struct	s_cam
{
	t_vec3f		pos;
	t_vec3f		dir;
}				t_cam;

typedef struct	s_data
{
	t_mainWindow	main_win;
	SDL_Event		events;
	t_time			time;
	t_hooks			hooks;
	t_player		player;
	SDL_Surface		*texture[4];
	t_cam			camera;
}				t_data;

typedef struct	s_args
{
	t_data		*d;
	t_vec2f		ray_dir;
	short		x;
	double		angle;
}				t_args;

#endif
