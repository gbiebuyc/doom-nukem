/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_doom.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 23:02:19 by nallani           #+#    #+#             */
/*   Updated: 2019/05/30 17:57:55 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_DOOM_H
# define STRUCTS_DOOM_H

typedef struct	s_3vec2f
{
	t_vec2f		start;
	t_vec2f		end;
	t_vec2f		scale;
}				t_3vec2f;

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
	int			cx1;
	int			cx2;
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
	double		*zbuffer;
	double		n;
	double		z;
	int			x;
	int			y;
	double		u;
	int			ya;
	int			yb;
	int			nya;
	int			nyb;
	bool		visible[WIDTH];
	double		doorheight;
	double		doorbottom;
	double		sin;
	double		cos;
}				t_projdata;

typedef struct	s_frustum
{
	int			ytop[WIDTH];
	int			ybottom[WIDTH];
	int			x1;
	int			x2;
	bool		visitedportals[MAXNUMWALLS];
}				t_frustum;

# define MAX_STATE 10

typedef struct	s_monster_type
{
	double		height;
	double		width;
	uint16_t	health;
	double		floating;
	uint8_t		id_sprite;
	uint8_t		anim_order[MAX_STATE];	
}				t_monster_type;

# define MAXNBOFANIMATION 5

typedef struct	s_data
{
	SDL_Window		*win;
	SDL_Surface		*screen;
	SDL_Surface		**textures;
	SDL_Surface		*monster_text[MAXTYPEMONSTERS][MAX_STATE][MAXNBOFANIMATION];
	int32_t			nb_textures;
	char			**tex_name_list;
	const Uint8		*keys;
	t_cam			cam;
	t_sector		sectors[MAXNUMSECTORS];
	t_wall			walls[MAXNUMWALLS];
	t_monster		monsters[MAXNUMMONSTERS];
	t_monster_type	monster_type[MAXTYPEMONSTERS];
	uint16_t		nummonsters;
	int16_t			numsectors;
	int16_t			numwalls;
	int16_t			cursectnum;
	bool			debug_pause;
	double			dooranimstep[MAXNUMWALLS];
	double			doorstate[MAXNUMWALLS];
	double			lightblink;
}				t_data;

#endif
