/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m16_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 14:59:13 by nallani           #+#    #+#             */
/*   Updated: 2019/06/29 15:28:35 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	set_pos_m16_inside_sec(t_data *d, int16_t id, t_vec2f *pos)
{
	*pos = d->monsters[id].pos;
	pos->x -= d->cam.pos.x;
	pos->y -= d->cam.pos.z;
	actualize_dir(d->cam.rot, pos);
	return (true);
}
