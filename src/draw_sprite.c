/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 02:27:33 by nallani           #+#    #+#             */
/*   Updated: 2019/05/07 08:55:52 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

// OPEN CIRCLE_ANIM on slack to understand code for 1rst function

uint8_t		get_nb_anim_from_rot(double monster_rot, 
		t_vec2f monster_pos, t_vec2f player_pos)// get the NB of the animation based on where does it face compared to where you are
	//code is in circle_anim on slack
{
	double	rot;
	double	vision_rot;
	t_vec2f	vision;

	vision = sub_vec2f(monster_pos, player_pos);
	vision_rot = atan2(vision.y, vision.x);
	rot = vision_rot - monster_rot;
	rot += M_PI_2 + M_PI * 2; // PANSEMENT ??
	if (rot > 2 * M_PI)
		rot -= 2 * M_PI;
	if (rot < 0)
		rot += 2 * M_PI;
	rot = rot -  0.125 * M_PI;
	if (rot > M_PI)
	{
		if (rot < 1.25 * M_PI)
			return (1);
		if (rot < 1.5 * M_PI)
			return (0);
		if (rot < 1.75 * M_PI)
			return (7);
		if (rot < 2 * M_PI)
			return (6);
	}
	if (rot > 0.75 * M_PI)
		return (2);
	if (rot > M_PI_2)
		return (3);
	if (rot > M_PI_4)
		return (4);
	if (rot < 0)
		return (6);
	return (5);
}

t_vec3f		get_projected_vertex(t_data *d, t_vec3f v, t_vec3f pos) // projection (for sprites only i think ?, unapplicable somewhere else)
{
	t_vec3f	new;
	t_vec3f dist;

	dist = sub_vec3f(pos, d->cam.pos);
	new = sub_vec3f(v, d->cam.pos);
	dist.z = dist.x * d->cam.sin + dist.z * d->cam.cos;
	new = (t_vec3f){
		new.x * d->cam.cos - new.z * d->cam.sin,
			new.y,
			new.x * d->cam.sin + new.z * d->cam.cos
	};
	new.x /= dist.z;
	new.y /= dist.z;
	new.x = new.x *  WIDTH + WIDTH / 2;
	new.y = new.y * -WIDTH + HEIGHT / 2 - d->cam.y_offset;
	return (new);
}

void	display_sprite(t_3vec2f a, t_data *d, SDL_Surface *s, bool rev) // display a sprite
	//a contains start end and scale values
	//rev is used to mirror an image
{
	int			x;
	int			y;
	int			colo;

	x = a.start.x + 1;
	while (x <= a.end.x)
	{
		y = a.start.y;
		while(y <= a.end.y)
		{
			if (rev)
				colo = getpixel(s, (1 - a.scale.x * (x - a.start.x)), a.scale.y * (y - a.start.y));
			else
				colo = getpixel(s, a.scale.x * (x - a.start.x), a.scale.y * (y - a.start.y));
			if (colo != 2037515) 
				putpixel(d, x, y, colo);
			y++;
		}
		x++;
	}
}

void	draw_sprite(t_data *d, t_projdata p, t_frustum *fr, int16_t monster_list) //main function to draw a sprite, need
	//to adjust start_x with fr (see problem below in comments)
{
	t_monster	monster;
	t_vec3f		top_left;
	t_vec3f		bot_right;
	t_vec3f		monsterpos;
	t_3vec2f	a;

	monster = d->monsters[p.sector->id_of_monster[monster_list]];
	monsterpos = (t_vec3f) {monster.pos.x, p.sector->floorheight + d->monster_type[monster.id_type].floating + monster.height, monster.pos.y};

	t_vec2f scale = (t_vec2f){monster.width, 0};
	actualize_dir(-d->cam.rot, &scale); // add ft_max entre pos du monstre et distance min pour affichage; //ou plutot
	// faire les collisions avec le joueur et empecher la bestiole d'avancer si trop proche ?
	top_left = get_projected_vertex(d, (t_vec3f){monsterpos.x - scale.x, monsterpos.y, monsterpos.z - scale.y}, monsterpos);
	bot_right = get_projected_vertex(d, (t_vec3f){monsterpos.x + scale.x,
			monsterpos.y + d->monster_type[monster.id_type].floating - monster.height, monsterpos.z + scale.y}, monsterpos);

	if (top_left.z > 0.4) //pansement
	{
		a.start.x = top_left.x > bot_right.x ? bot_right.x : top_left.x ;
		//		a.start.x = ft_max(begin_x, fr->x1);// problem : besoin de faire en sorte que le sprite en sorte pas de la fenetre du secteur
		//		(pas simplement du dernier mur du secteur)
		a.end.x = top_left.x > bot_right.x ? top_left.x : bot_right.x;
		//		a.end_x = ft_min(end_x, fr->x2);
		a.scale.x = fabs(100.0 / (a.start.x - a.end.x) / 100);
		a.start.y = bot_right.y > top_left.y ? top_left.y : bot_right.y;
		a.end.y = bot_right.y > top_left.y ? bot_right.y : top_left.y;
		a.scale.y = fabs((100.0 / (a.start.y - a.end.y)) / 100);
		int nb_of_anim = get_nb_anim_from_rot(monster.rot, monster.pos, vec3to2(d->cam.pos));
		if (nb_of_anim > 4)
		{
			nb_of_anim = 8 - nb_of_anim; 
			display_sprite(a, d, d->monster_text[monster.id_type][nb_of_anim], false);
		}
		else
			display_sprite(a, d, d->monster_text[monster.id_type][nb_of_anim], true);
	}
	if (p.sector->id_of_monster[++monster_list] != -1) //recursive call for all monsters in a sector (/!\ need to sort them before first call)
		draw_sprite(d, p, fr, monster_list);
}
