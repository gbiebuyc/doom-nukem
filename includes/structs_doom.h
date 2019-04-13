/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_doom.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 23:02:19 by nallani           #+#    #+#             */
/*   Updated: 2019/04/13 04:29:40 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_DOOM_H
#define STRUCTS_DOOM_H
#include "../SDL/library/include/SDL2/SDL.h"

enum	e_texture_order
{
	TOP_LEFT, TOP_RIGHT, BOT_LEFT, BOT_RIGHT
};

typedef struct	s_24_t
{
	uint32_t value : 24;
}				t_24_t;

enum			e_enums
{
	FORWARD = 1,
	BACKWARD,
	LEFT_STRAFE,
	RIGHT_STRAFE,
	LEFT_TURN,
	RIGHT_TURN,
	UP_FLY,
	DOWN_FLY
};

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

typedef struct	s_texture2d
{
	t_vec2f		vertex[4];
}				t_texture2d;

typedef struct	s_texture3d
{
	t_vec3f		vertex[4];
}				t_texture3d;


typedef struct	s_keystate
{
	char		dir;
	char		strafe_dir;
	char		hor_turn;
	char		ver_dir;
}				t_keystate;

typedef struct	s_player
{
	t_vec3f		pos;
	t_vec2f		dir;
	t_vec2f		plane;
}				t_player;

typedef struct	s_mainWindow
{
	SDL_Window	*win;
	SDL_Surface	*surface;
}				t_mainWindow;

typedef	struct	s_time
{
	struct timeval	tod;
	struct timeval	ini_time;
	// ptet stocker la diff pour utiliser sur un autre event que dans loop ?
}				t_time;

typedef struct	s_cam
{
	t_vec3f		pos;
	t_vec3f		rot;
	double		sin_x;
	double		cos_x;
	double		sin_y;
	double		cos_y;
}				t_cam;

typedef struct	s_sector
{
	int16_t		headwall;
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

}				t_wall;

typedef struct	s_thing
{
	t_vec2f		pos;
	float		angle;
	int16_t		picnum;
	int16_t		flags;
}				t_thing;

typedef struct	s_data
{
	t_mainWindow	main_win;
	SDL_Event		events;
	t_time			time;
	t_keystate		keys;
	t_player		player;
	SDL_Surface		*texture[4];
	t_cam			cam;
	t_sector		sectors[1024];
	t_wall			walls[8192];
	int16_t			numsectors;
	int16_t			numwalls;
}				t_data;

typedef struct	s_args
{
	t_data		*d;
	t_vec2f		ray_dir;
	short		x;
	double		angle;
}				t_args;

#endif
