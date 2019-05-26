/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_editor_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 23:17:07 by mikorale          #+#    #+#             */
/*   Updated: 2019/05/17 23:17:09 by mikorale         ###   ########.fr       */
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
	d->walls[d->numwalls - 1].point = p;
	d->walls[d->numwalls - 1].neighborsect = -1;
	d->selectedwall = &d->walls[d->numwalls - 1];
}

/*
**	Find closest wall. Priority to walls that have a neighbor.
*/

static void	find_wall(t_data *d, t_vec2f *p, double min_dist, t_wall *wall)
{
	t_vec2f p2;
	double	dist;

	//t_vec2f	next_wall;
	while (wall - d->walls < d->numwalls)
	{
		p2 = worldtoscreen(d, wall->point);
		//next_wall = worldtoscreen(d, (wall + 1)->point);
		dist = vec2f_length((t_vec2f){p->x - p2.x, p->y - p2.y});
	/*	if (((p.x >= p2.x - 15 && p.x <= next_wall.x + 15 && p.y >= p2.y - 15 && p.y <= next_wall.y + 15)
			|| (p.x <= p2.x + 15 && p.x >= next_wall.x - 15 && p.y <= p2.y + 15 && p.y >= next_wall.y - 15))*/
		if (dist < 15 && ((dist < min_dist) ||
			(dist == min_dist && wall->neighborsect != -1)))
		{
			d->selectedwall = wall;
			d->selected_wall = wall - d->walls;
			min_dist = dist;
			/**/ft_printf("Wall %d selected\n", d->selectedwall - d->walls);
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
	if (d->selectedwall && d->selectedwall->neighborsect != -1)
	{
		i = 0;
		neighborsect = &d->sectors[d->selectedwall->neighborsect];
		while (i++ < neighborsect->numwalls)
		{
			wall = d->walls + neighborsect->firstwallnum + i;
			if (same_pos(wall, d->selectedwall))
			{
				d->selectedwall2 = wall;
				break ;
			}
		}
	}
	if (!d->selectedwall)
		d->selected_wall = -1;
	update_wall_pos(d);
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