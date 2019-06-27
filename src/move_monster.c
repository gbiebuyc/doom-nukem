/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_monster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:58:22 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/26 15:58:22 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MONSTER_SPEED 0.02

t_vec2f	random_vector(void)
{
	static int		random;
	double			a;
	double			len;

	random += SDL_GetTicks() * 42;
	a = random % 360 * M_PI / 180;
	len = random % 200 / 200.0 + 1.0;
	return ((t_vec2f){len * cos(a), len * sin(a)});
}

void	move_monster(t_data *d, int i)
{
	t_vec2f	step;
	t_vec2f	new_target;
	double	len;

	if (d->monsters[i].life <= 0)
		return ;
	step = sub_vec2f(d->monster_target[i], d->monsters[i].pos);
	if ((len = vec2f_length(step)) < MONSTER_SPEED)
	{
		new_target = add_vec2f(d->monsters[i].pos, random_vector());
		while (!inside(d, d->monsters[i].cursectnum, new_target))
			new_target = add_vec2f(d->monsters[i].pos, random_vector());
		d->monster_target[i] = new_target;
		move_monster(d, i);
		return ;
	}
	step = mul_vec2f(step, MONSTER_SPEED / len);
	d->monsters[i].pos = add_vec2f(d->monsters[i].pos, step);
}
