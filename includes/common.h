/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:09:25 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/29 21:30:38 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <SDL.h>
# include <libft.h>
# include <../SDL2_mixer/SDL_mixer.h>

/*
** This header is used both by the editor and the game
*/

# define MAXNUMSECTORS 1024
# define MAXNUMMONSTERS 256
# define MAXNUMWALLS 4096
# define MAXTYPEMONSTERS 2

typedef struct				s_font
{
	char					*str;
	int						x;
	int						y;
	uint32_t				color;
	int						scale;
}							t_font;

typedef struct				s_vec3f
{
	double					x;
	double					y;
	double					z;
}							t_vec3f;

typedef struct				s_vec2f
{
	double					x;
	double					y;
}							t_vec2f;

typedef struct				s_vec2
{
	int						x;
	int						y;
}							t_vec2;

# define IS_PROJECTILE 0
# define IS_MONSTER 1
# define CRYO_BALLISTA 0
# define BLASTER 1
# define M16 2
# define FIREBALL_1 1

typedef struct				s_sprite_list
{
	int16_t					id;
	struct s_sprite_list	*next;
	uint8_t					type;
}							t_sprite_list;

typedef struct				s_sector
{
	int16_t					firstwallnum;
	int16_t					numwalls;
	float					floorheight;
	float					ceilheight;
	int16_t					floorpicnum;
	int16_t					ceilpicnum;
	float					light;
	bool					blinking;
	char					floor_texture_name[100];
	char					ceil_texture_name[100];
	bool					outdoor;
	t_sprite_list			*sprite_list;
	int16_t					slope;
	int16_t					slope_orientation;
	int16_t					slopeceil;
	int16_t					slopeceil_orientation;
	bool					is_animatedslope;
	bool					is_animatedslopeceil;
	bool					is_elevator;
	bool					is_finish;
	bool					is_harmful;
}							t_sector;

typedef struct				s_wall
{
	t_vec2f					point;
	int16_t					upperpicnum;
	int16_t					middlepicnum;
	int16_t					lowerpicnum;
	int16_t					flags;
	int16_t					neighborsect;
	char					texture_name[100];
	char					poster_name[100];
	bool					is_door;
	int						door_num;
	int						key_num;
	int16_t					posterpicnum;
	bool					is_transparent;
}							t_wall;

typedef struct				s_stat_modifier
{
	int16_t					heal;
	int16_t					damage;
	int16_t					ballista_ammo;
	int16_t					blaster_ammo;
	int16_t					m16_ammo;
}							t_stat_modifier;

typedef struct				s_assets
{
	int						nb_assets;
	int						picnum;
	t_vec2f					world_pos;
	bool					is_on_floor;
	bool					is_on_ceil;
	t_stat_modifier			stat_mod;
	bool					is_interactive;
	bool					is_autopick;
	bool					collision;
	bool					is_jetpack;
	bool					is_key;
	int						key_num;
	bool					used;
}							t_assets;

# define MOTHERDEMON 0
# define CHARGINGDEMON 1

typedef struct				s_monster
{
	t_vec2f					pos;
	t_vec2f					dir;
	double					rot;
	int16_t					cursectnum;
	uint8_t					id_type;
	uint8_t					anim_state;
	uint8_t					anim_time;
	uint8_t					timer;
	int16_t					life;
	bool					can_collide;
	bool					activated;
}							t_monster;

typedef struct				s_texture_data
{
	char					name[100];
	int						used;
	struct s_texture_data	*begin;
	struct s_texture_data	*prev;
	struct s_texture_data	*next;
}							t_texture_data;

/*
** vec2.c
*/

t_vec2f						sub_vec2f(t_vec2f v1, t_vec2f v2);
t_vec2f						add_vec2f(t_vec2f v1, t_vec2f v2);
void						actualize_dir(double angle, t_vec2f *vec);
t_vec3f						sub_vec3f(t_vec3f v1, t_vec3f v2);
t_vec3f						mul_vec3f(t_vec3f v1, double scalar);

/*
** vec2_2.c
*/

t_vec2f						mul_vec2f(t_vec2f v, double scalar);
float						get_vec2f_length(t_vec2f v);
double						vec2f_length(t_vec2f v);
double						get_vec2f_angle(t_vec2f v1, t_vec2f v2);
t_vec3f						add_vec3f(t_vec3f a, t_vec3f b);

#endif
