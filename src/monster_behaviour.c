/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_behaviour.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 22:40:39 by nallani           #+#    #+#             */
/*   Updated: 2019/06/08 20:03:22 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

# define ACTIVATION_RADIUS 10

void	monster_behaviour(t_data *d, t_monster *monster)
{
	static	int i;
	t_vec2f	tmp;

	if (!monster->can_collide) // all monster collide so far, used for monster is dead
		return ;
	if (!monster->activated)
	{
		if (get_vec2f_length(sub_vec2f(monster->pos, vec3to2(d->cam.pos))) < ACTIVATION_RADIUS)
			monster->activated = true;
		else
			return ;
	}
	if (i == 100)
	{
		tmp = sub_vec2f(vec3to2(d->cam.pos), monster->pos);
		monster->anim_state = 4;
		monster->anim_time = 10;
		monster->rot = atan2(tmp.y, tmp.x);
		i = 0;
	}
	i++;
}
