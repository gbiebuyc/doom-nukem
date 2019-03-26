/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:53:29 by nallani           #+#    #+#             */
/*   Updated: 2019/03/26 00:26:01 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
#define DOOM_NUKEM_H

#include "structs_doom.h"
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"
#include <sys/time.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#define WIN_WIDTH 800
#define WIN_LENGTH 600

/*
** exit.c
*/

void	proper_exit(t_data *d);
void	err_exit(t_data *d, char count, const char *msg);

/*
** init_sdl.c
*/

void	ft_init_sdl(t_data *d, int width, int length);

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

/*
** ini.c
*/

void	ini_player(t_data *d);

/*
** refresh.c
*/

void	refresh_img(t_data *d);

/*
** intersection.c
*/

void	find_intersection(t_args *args);

/*
** vec2.c
*/

t_vec2f			sub_vec2f(t_vec2f v1, t_vec2f v2);
t_vec2f			add_vec2f(t_vec2f v1, t_vec2f v2);
void			actualize_dir(double angle, t_vec2f *vec);

/*
** vec2_2.c
*/

t_vec2f			mul_vec2f(t_vec2f v, double scalar);
float			get_vec2f_length(t_vec2f v);
double			vec2f_length(t_vec2f v);
double			get_vec2f_angle(t_vec2f v1, t_vec2f v2);

#endif
