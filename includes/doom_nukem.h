/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:53:29 by nallani           #+#    #+#             */
/*   Updated: 2019/04/26 18:22:54 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
#define DOOM_NUKEM_H

#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"
#include <sys/time.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>

#define WIDTH 800
#define HEIGHT 600
#define FOV 1
#define MAXNUMSECTORS 1024
#define MAXNUMWALLS 8192
#include <structs_doom.h>

/*
** projection.c
*/

void	apply_transform(t_data *d, t_vec3f *v);
t_vec3f	apply_perspective(t_data *d, t_vec3f v);
void	draw_texture(t_data *d, t_texture3d text, SDL_Surface surface);

void	square(t_data *d);
void	putpixel(t_data *d, int x, int y, uint32_t color);
uint32_t	getpixel(SDL_Surface *s, double x, double y);
uint32_t	getpixel2(SDL_Surface *s, double x, double y);
uint32_t	rgb_to_pixel(SDL_Surface *surface, int r, int g, int b);
void	draw_wall(t_data *d, t_wall_clipped wall);
void	draw_floor(t_data *d, t_wall_clipped wall);
void	load_map(t_data *d);
bool	inside(t_data *d, int16_t sectnum);
t_vec3f	vec2to3(t_vec2f v);
t_vec2f	vec3to2(t_vec3f v);
bool	clip_wall(t_vec3f *p0, t_vec3f p1);

/*
** utils.c
*/

double	lerp(double norm, double min, double max);
double	norm(double val, double min, double max);
int		clamp(int x, int min, int max);
double	fclamp(double x, double min, double max);

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
** motion_event.c
*/

void	event_mouse_motion(t_data *d, SDL_MouseMotionEvent event);

/*
** mouse_event.c
*/

void	event_mouse_button(t_data *d, SDL_MouseButtonEvent event);

/*
** key_event.c
*/

void	event_key_down(t_data *d, SDL_KeyboardEvent event);
void	event_key_up(t_data *d, SDL_KeyboardEvent event);

/*
** window_event.c
*/

void	event_window(t_data *d, SDL_WindowEvent event);

/*
** ini.c
*/

void	ini_player(t_data *d);
void	init_scene(t_data *d);

/*
** refresh.c
*/

void	refresh_img(t_data *d);
void	refresh_game(t_data *d);

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
t_vec3f			sub_vec3f(t_vec3f v1, t_vec3f v2);
t_vec3f 		mul_vec3f(t_vec3f v1, double scalar);

/*
** vec2_2.c
*/

t_vec2f			mul_vec2f(t_vec2f v, double scalar);
float			get_vec2f_length(t_vec2f v);
double			vec2f_length(t_vec2f v);
double			get_vec2f_angle(t_vec2f v1, t_vec2f v2);
t_vec3f			add_vec3f(t_vec3f a, t_vec3f b);

#endif
