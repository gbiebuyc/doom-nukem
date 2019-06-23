/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_editor_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 23:17:07 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/14 18:56:33 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
**  Check if there is already a wall at this point.
*/

static int	is_there_a_wall(t_data *d, t_sector *sect)
{
	int		i;
	t_wall	*wall;

	i = -1;
	while (++i < sect->numwalls - 1)
	{
		wall = d->walls + sect->firstwallnum + i;
		if (same_pos(wall, d->selectedwall))
			return (1);
	}
	return (0);
}

/*
**	To complete a sector you  must press the
**	space bar at the first point again.
*/

void		add_wall(t_data *d)
{
	int			x;
	int			y;
	t_sector	*sect;
	t_wall		*wall;
	t_vec2f		p;

	sect = &d->sectors[d->numsectors - 1];
	wall = d->walls + sect->firstwallnum;
	if (sect->numwalls >= 2 && same_pos(wall, d->selectedwall))
	{
		d->numwalls--;
		sect->numwalls--;
		d->sectordrawing = false;
		return ;
	}
	if (is_there_a_wall(d, sect))
		return ;
	d->numwalls++;
	sect->numwalls++;
	SDL_GetMouseState(&x, &y);
	p = grid_lock(d, screentoworld(d, (t_vec2f){x, y}));
	d->walls[d->numwalls - 1] = (t_wall){p, d->default_wall_texture,
		d->default_wall_texture, d->default_wall_texture, 0, -1, "", 0, -1,
		0, -1, false};
	d->selectedwall = &d->walls[d->numwalls - 1];
}

/*
**	Find closest wall. Priority to walls that have a neighbor.
*/

static void	find_wall(t_data *d, t_vec2f *p, double min_dist, t_wall *wall)
{
	t_vec2f w;
	double	dist;

	while (wall - d->walls < d->numwalls)
	{
		w = worldtoscreen(d, wall->point);
		dist = vec2f_length((t_vec2f){p->x - w.x, p->y - w.y});
		if (dist < 15 && ((dist < min_dist) || (dist == min_dist &&
			wall->neighborsect != -1)))
		{
			d->selected_wall = wall - d->walls;
			d->selectedwall = wall;
			min_dist = dist;
			if (d->selectedwall != NULL && d->interface.separate_sector)
				break ;
		}
		wall++;
	}
}

/*
**	Select the wall we clicked on, and find his neighbor wall if there is one.
*/

void		select_wall_under_cursor(t_data *d, t_vec2f p)
{
	int			i;
	t_wall		*wall;
	t_sector	*neighborsect;

	d->selectedwall = NULL;
	d->selectedwall2 = NULL;
	wall = d->walls;
	find_wall(d, &p, INFINITY, wall);
	if (d->selectedwall && d->selectedwall->neighborsect != -1
		&& !d->interface.separate_sector)
	{
		i = -1;
		neighborsect = &d->sectors[d->selectedwall->neighborsect];
		while (++i < neighborsect->numwalls)
		{
			wall = d->walls + neighborsect->firstwallnum + i;
			if (same_pos(wall, d->selectedwall))
				d->selectedwall2 = wall;
		}
	}
	if (!d->selectedwall)
		d->selected_wall = -1;
}

void		update_wall_pos(t_data *d)
{
	int		x;
	int		y;
	t_vec2f	p;

	if (!d->selectedwall)
		return ;
	SDL_GetMouseState(&x, &y);
	p = grid_lock(d, screentoworld(d, (t_vec2f){x, y}));
	d->selectedwall->point = p;
	if (d->selectedwall2)
		d->selectedwall2->point = p;
	else
		detect_neighbors(d, in_which_sector_is_this_wall(d, d->selectedwall));
}
