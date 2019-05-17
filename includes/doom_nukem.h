/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:53:29 by nallani           #+#    #+#             */
/*   Updated: 2019/05/12 17:52:58 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <common.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>

# define WIDTH 800
# define HEIGHT 600
# define FPS 60
# include <structs_doom.h>

void	putpixel(t_data *d, int x, int y, uint32_t color);
uint32_t	getpixel(SDL_Surface *s, double x, double y);
uint32_t	getpixel2(SDL_Surface *s, double x, double y);
uint32_t	bmpgetpixel(t_bitmap b, double x, double y);
uint32_t	bmpgetpixel2(t_bitmap b, double x, double y);
void	load_map(t_data *d, char *p);
bool	inside(t_data *d, int16_t sectnum);
bool	clip_wall(double *x1, double *z1, double x2, double z2);
void	draw_wall(t_data *d, t_projdata *p, t_frustum *fr);
void	draw_floor(t_data *d, t_projdata p, t_frustum *fr);
void	clamp_wall(bool visible[], int *x1, int *x2);
void	update(t_data *d);
void	render(t_data *d);
void	render_sector(t_data *d, t_sector *sect, t_frustum *fr);
void	draw_sprite(t_data *d, t_projdata p, t_frustum *fr, int16_t id_of_monster);
void	init_monsters(t_data *d);
void	monster_anim_state(t_monster *monster, t_monster_type *monster_type);
void	monster_behaviour(t_data *d, t_monster *monster);
uint32_t	shade(double z, uint32_t c);
t_vec3f		vec2to3(t_vec2f v);
t_vec2f		vec3to2(t_vec3f v);
void	load_tex(t_data *d, char *p);
int		parseoct(const char *p, size_t n);

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
void	jump(t_data *d, bool pressed);

/*
** movement.c
*/

void	movement(t_data *d);

#endif
