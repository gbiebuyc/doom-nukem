/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 02:27:33 by nallani           #+#    #+#             */
/*   Updated: 2019/05/07 03:55:29 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
t_vec3f		get_projected_vertex(t_data *d, t_vec3f v, t_vec3f pos)
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

void draw_sprite(t_data *d, t_projdata p, t_frustum *fr, uint8_t monster_list)
{
	t_monster	monster;
	t_vec3f		top_left;
	t_vec3f		bot_right;
	t_vec3f		monsterpos;

	monster = d->monsters[p.sector->id_of_monster[monster_list] - 1];
	monsterpos = (t_vec3f) {monster.pos.x, p.sector->floorheight + 0.1 + d->monster_type[monster.id_type].height * monster.size, monster.pos.y};

	t_vec2f scale = (t_vec2f){d->monster_type[monster.id_type].width * monster.size, 0};
	actualize_dir(-d->cam.rot, &scale); // add ft_max entre pos du monstre et distance min pour affichage;
	top_left = get_projected_vertex(d, (t_vec3f){monsterpos.x - scale.x, monsterpos.y, monsterpos.z - scale.y}, monsterpos);
	bot_right = get_projected_vertex(d, (t_vec3f){monsterpos.x + scale.x,
			monsterpos.y + 0.1 - d->monster_type[monster.id_type].height * monster.size, monsterpos.z + scale.y}, monsterpos);

	double begin_x = top_left.x > bot_right.x ? bot_right.x : top_left.x;
	if (top_left.z > 0.3)
	for (int x = begin_x; x < end_x; x++)
	{
		double scale_x = fabs((100.0 / (begin_x - end_x)) * (x - begin_x)) / 100;
		double begin_y = bot_right.y > top_left.y ? top_left.y : bot_right.y;
		double end_y = bot_right.y > top_left.y ? bot_right.y : top_left.y;
		for (int y = begin_y; y < end_y; y++)
		{
			double scale_y = fabs((100.0 / (begin_y - end_y)) * (y - begin_y)) / 100;
			uint32_t colo = getpixel(d->monster_text[monster.id_type][monster.anim], scale_x, scale_y);
			if (colo != 2037515)
			putpixel(d, x, y, colo);
		}
	}
		if (p.sector->id_of_monster[++monster_list])
	draw_sprite(d, p, fr, monster_list);
}
