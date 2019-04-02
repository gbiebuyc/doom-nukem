/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 04:14:37 by nallani           #+#    #+#             */
/*   Updated: 2019/04/02 15:21:59 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


void	event_key_down(t_data *d, SDL_KeyboardEvent event)
{
	if (event.keysym.sym == SDLK_ESCAPE)
		proper_exit(d);

	t_vec2f newpos = (t_vec2f){d->camera.pos.x, d->camera.pos.z};
	// Deplacement
	if (event.keysym.sym == SDLK_w)
		newpos = add_vec2f(newpos, mul_vec2f((t_vec2f){d->camera.dir.x, d->camera.dir.z}, 0.1));
	if (event.keysym.sym == SDLK_s)
		newpos = add_vec2f(newpos, mul_vec2f((t_vec2f){d->camera.dir.x, d->camera.dir.z}, -0.1));
	if (event.keysym.sym == SDLK_a)
	{
		t_vec2f dirtmp = (t_vec2f){d->camera.dir.x, d->camera.dir.z};
		actualize_dir(M_PI_2, &dirtmp);
		//printf("x:%f z:%f,    x:%f z:%f\n", d->camera.dir.x, d->camera.dir.z, dirtmp.x, dirtmp.y);
		newpos = add_vec2f(newpos, mul_vec2f(dirtmp, 0.1));
	}
	if (event.keysym.sym == SDLK_d)
	{
		t_vec2f dirtmp = (t_vec2f){d->camera.dir.x, d->camera.dir.z};
		actualize_dir(-M_PI_2, &dirtmp);
		//printf("x:%f z:%f,    x:%f z:%f\n", d->camera.dir.x, d->camera.dir.z, dirtmp.x, dirtmp.y);
		newpos = add_vec2f(newpos, mul_vec2f(dirtmp, 0.1));
	}
	//printf("ancienne: %f, %f,     new: %f, %f\n", d->camera.pos.x, d->camera.pos.z, newpos.x, newpos.y);
	d->camera.pos = (t_vec3f){newpos.x, d->camera.pos.y, newpos.y};

	// Tourner
	t_vec2f newrot = (t_vec2f){d->camera.dir.x, d->camera.dir.z};
	if (event.keysym.sym == SDLK_LEFT)
		actualize_dir(0.1, &newrot);
	if (event.keysym.sym == SDLK_RIGHT)
		actualize_dir(-0.1, &newrot);
	d->camera.dir = (t_vec3f){newrot.x, d->camera.dir.y, newrot.y};
	//printf("x:%f z:%f\n", d->camera.dir.x, d->camera.dir.z);

	// Altitude
	if (event.keysym.sym == SDLK_UP)
		d->camera.pos.y += 0.1;
	if (event.keysym.sym == SDLK_DOWN)
		d->camera.pos.y -= 0.1;
}
