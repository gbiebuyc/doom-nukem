/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:09:25 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/30 07:12:25 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <SDL.h>
# include <libft.h>

/*
** This header is used both by the editor and the game
*/

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

typedef struct	s_vec2
{
	int			x;
	int			y;
}				t_vec2;

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

typedef struct	s_thing
{
	t_vec2f		pos;
	float		angle;
	int16_t		picnum;
	int16_t		flags;
}				t_thing;

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