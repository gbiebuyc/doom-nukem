/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:09:25 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/07 23:12:23 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <SDL.h>
# include <libft.h>

/*
** This header is used both by the editor and the game
*/

# define MAXMONSTERSEC 20
# define MAXNUMSECTORS 1024
# define MAXNUMMONSTERS 256
# define MAXNUMWALLS 4096
# define MAXTYPEMONSTERS 2

typedef struct	s_font
{
	char		*str;
	int			x;
	int			y;
	uint32_t	color;
	int			scale;
}				t_font;

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

# define IS_PROJECTILE 0
# define IS_MONSTER 1
# define CRYO_BALLISTA 0
# define BLASTER 1
# define M16 2
# define FIREBALL_1 1

typedef struct	s_sprite_list
{
	int16_t					id;
	struct s_sprite_list	*next;
	uint8_t 				type;
}				t_sprite_list;

typedef struct	s_sector
{
	int16_t		firstwallnum;
	int16_t		numwalls;
	float		floorheight;
	float		ceilheight;
	int16_t		floorpicnum;
	int16_t		ceilpicnum;
	float		light;
	bool		blinking;
	char		floor_texture_name[100];
	char		ceil_texture_name[100];
	bool		outdoor;
	t_sprite_list	*sprite_list;
	int16_t		slope; // between -90 and 90 degrees
	int16_t		slopeceil;
}				t_sector;

typedef struct	s_wall
{
	t_vec2f		point;
	int16_t		upperpicnum;
	int16_t		middlepicnum;
	int16_t		lowerpicnum;
	int16_t		flags;
	int16_t		neighborsect;
	char		texture_name[100];
	bool		is_door;
	int16_t		posterpicnum;
}				t_wall;

typedef struct	s_thing
{
	t_vec2f		pos;
	float		angle;
	int16_t		picnum;
	int16_t		flags;
}				t_thing;

# define MOTHERDEMON 0

typedef struct	s_monster
{
	t_vec2f		pos; //position du monstre en x et z
	double		size; // scale de la taille par rapport a la taille du monstre type (a exprimer em %)
	double		health_mult; // scale de la vie par rapport a la vie du monstre type
	double		rot; // set in editor, where is the monster looking at first 
	int16_t		cursectnum; // set in editor, which sector is the monster from
	uint8_t		id_type; // which type is the monster (use defines <- NO !)
	//double	floating; // might be used to set different floating height for monsters
	uint8_t		anim_state; // set during behaviour to chose which state of animation is the monster in
	uint8_t		anim_time;
	uint8_t		behaviour; // set in editor (to be discussed ?), id of behavior to follow for the monster// not used yet
	uint8_t		timer; // used to time actions
	int16_t		life; //life calculated in binary
	double		height; // calculee dans le binaire
	double		width; // calculee dans le binaire
	bool		can_collide; // collides or not with player(used when monster is dead)
	bool		activated; // unused for now

}				t_monster;

typedef struct	s_texture_data
{
	char					name[100];
	int						used;
	struct s_texture_data	*begin;
	struct s_texture_data	*prev;
	struct s_texture_data	*next;
}				t_texture_data;

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
