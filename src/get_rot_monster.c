/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rot_monster.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 12:44:24 by nallani           #+#    #+#             */
/*   Updated: 2019/06/29 12:54:32 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

uint8_t	get_nb_anim_from_rot_2(double rot)
{
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

uint8_t	get_nb_anim_from_rot(double monster_rot,
		t_vec2f monster_pos, t_vec2f player_pos)
{
	double	rot;
	double	vision_rot;
	t_vec2f	vision;

	vision = sub_vec2f(monster_pos, player_pos);
	vision_rot = atan2(vision.y, vision.x);
	rot = vision_rot - monster_rot;
	rot += M_PI_2;
	if (rot > 2 * M_PI)
		rot -= 2 * M_PI;
	if (rot < 0)
		rot += 2 * M_PI;
	rot = rot - 0.125 * M_PI;
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
	return (get_nb_anim_from_rot_2(rot));
}
