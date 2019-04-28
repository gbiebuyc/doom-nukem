/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_doom.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 23:02:19 by nallani           #+#    #+#             */
/*   Updated: 2019/04/30 00:14:55 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_DOOM_H
# define STRUCTS_DOOM_H
# include "../SDL/library/include/SDL2/SDL.h"

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

typedef struct	s_cam
{
	t_vec3f		pos;
	double		rot;
	double		sin;
	double		cos;
	double		y_offset;
}				t_cam;

typedef struct	s_sector
{
	int16_t		firstwallnum;
	int16_t		numwalls;
	float		floorheight;
	float		ceilheight;
	int16_t		floorpicnum;
	int16_t		ceilpicnum;
	uint8_t		light;
}				t_sector;

typedef struct	s_wall
{
	t_vec2f		point;
	int16_t		upperpicnum;
	int16_t		middlepicnum;
	int16_t		lowerpicnum;
	int16_t		flags;
	int16_t		neighborsect;
}				t_wall;

typedef struct	s_projdata
{
	double		x1;
	double		x2;
	double		z1;
	double		z2;
	int			y1a;
	int			y2a;
	int			y1b;
	int			y2b;
	t_sector	*neighbor;
	int			ny1a;
	int			ny2a;
	int			ny1b;
	int			ny2b;
	double		u_begin;
	double		u_end;
	double		y_scale;
	t_wall		*wall;
	t_sector	*sector;
}				t_projdata;

typedef struct	s_thing
{
	t_vec2f		pos;
	float		angle;
	int16_t		picnum;
	int16_t		flags;
}				t_thing;

typedef struct	s_frustum
{
	int			ytop[WIDTH];
	int			ybottom[WIDTH];
	int			x1;
	int			x2;
}				t_frustum;

typedef struct	s_data
{
	SDL_Window		*win;
	SDL_Surface		*screen;
	SDL_Surface		*textures[4];
	const Uint8		*keys;
	t_cam			cam;
	t_sector		sectors[MAXNUMSECTORS];
	t_wall			walls[MAXNUMWALLS];
	int16_t			numsectors;
	int16_t			numwalls;
	int16_t			cursectnum;
}				t_data;

#endif
