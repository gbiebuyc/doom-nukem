/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_doom.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 23:02:19 by nallani           #+#    #+#             */
/*   Updated: 2019/04/30 00:16:30 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_DOOM_H
# define STRUCTS_DOOM_H

typedef struct	s_cam
{
	t_vec3f		pos;
	double		rot;
	double		sin;
	double		cos;
	double		y_offset;
}				t_cam;

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
