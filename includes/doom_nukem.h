/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:53:29 by nallani           #+#    #+#             */
/*   Updated: 2019/05/07 00:51:42 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <common.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>

# define WIDTH 800
# define HEIGHT 600
# define FPS 60
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
void	draw_sprite(t_data *d, t_projdata p, t_frustum *fr, uint8_t id_of_monster);
void	init_monsters(t_data *d);

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
** ini*/

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
** jump.c
*/

void	gravity(t_data *d, int mod);
void	jump(t_data *d);

/*
** movement.c
*/

void	movement(t_data *d);

#endif
