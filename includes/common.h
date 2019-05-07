/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:09:25 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/07 07:37:32 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <SDL.h>
# include <libft.h>

# define MAXMONSTERSEC 20
# define MAXNUMSECTORS 1024
# define MAXNUMMONSTERS 256
# define MAXNUMWALLS 8192
# define MAXTYPEMONSTERS 2

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
	int16_t		id_of_monster[MAXMONSTERSEC];
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

typedef struct	s_monster
{
	t_vec2f		pos; //position du monstre en x et z
	double		size; // scale de la taille par rapport a la taille du monstre type (a exprimer em %)
	double		height; // calculee dans le binaire
	double		width; // calculee dans le binaire
	double		health_mult; // scale de la vie par rapport a la vie du monstre type
	double		rot; // unused for now, will be used to chose animation displayed
	int16_t		life; //life calculated in binary
	int16_t		sector; // which sector is the monster from
	uint8_t		id_type; // which type is the monster
	//double	floating; // might be used to set different floating height for monsters
	uint8_t		anim; // unused for now
	void		(*behavior)(/*add stuff there*/); //maybe do it with a if (id == 1) then call behaviour_1()...
	 // behavior unused for now
	bool		activated; // unused for now
}				t_monster;

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
