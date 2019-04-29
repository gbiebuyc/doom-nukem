/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:53:29 by nallani           #+#    #+#             */
/*   Updated: 2019/04/30 00:01:29 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <SDL.h>
# include <libft.h>
# include <common_structs.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>

# define WIDTH 800
# define HEIGHT 600
# define FPS 60
# define MAXNUMSECTORS 1024
# define MAXNUMWALLS 8192
# include <structs_doom.h>

void	putpixel(t_data *d, int x, int y, uint32_t color);
uint32_t	getpixel(SDL_Surface *s, double x, double y);
uint32_t	getpixel2(SDL_Surface *s, double x, double y);
void	load_map(t_data *d);
bool	inside(t_data *d, int16_t sectnum);
bool	clip_wall(double *x1, double *z1, double x2, double z2);
void	draw_wall(t_data *d, t_projdata p, t_frustum *fr);
void	draw_floor(t_data *d, t_projdata p, t_frustum *fr);
void	update(t_data *d);
void	render(t_data *d);
void	render_sector(t_data *d, t_sector *sect, t_frustum *fr);

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

void	init_sdl(t_data *d);

/*
** loop.c
*/

void	loop(t_data *d);

/*
** events.c
*/

void	event_mouse_motion(t_data *d, SDL_MouseMotionEvent event);
void	event_mouse_button(t_data *d, SDL_MouseButtonEvent event);
void	event_key_down(t_data *d, SDL_KeyboardEvent event);

/*
** vec2.c
*/

t_vec2f			sub_vec2f(t_vec2f v1, t_vec2f v2);
t_vec2f			add_vec2f(t_vec2f v1, t_vec2f v2);
void			actualize_dir(double angle, t_vec2f *vec);
t_vec3f			sub_vec3f(t_vec3f v1, t_vec3f v2);
t_vec3f			mul_vec3f(t_vec3f v1, double scalar);

/*
** vec2_2.c
*/

t_vec2f			mul_vec2f(t_vec2f v, double scalar);
float			get_vec2f_length(t_vec2f v);
double			vec2f_length(t_vec2f v);
double			get_vec2f_angle(t_vec2f v1, t_vec2f v2);
t_vec3f			add_vec3f(t_vec3f a, t_vec3f b);

#endif
