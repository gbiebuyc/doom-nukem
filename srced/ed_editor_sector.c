/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_editor_sector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 18:46:41 by mikorale          #+#    #+#             */
/*   Updated: 2019/05/15 18:46:42 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		check_if_assets_inside_sector(t_data *d)
{
	t_monster_list	*ml;
	t_monster_list	*mtmp;
	t_assets_list	*al;
	t_assets_list	*atmp;
 
	ml = (d->interface.monster_list) ? d->interface.monster_list->begin : NULL;
	al = (d->interface.assets_list) ? d->interface.assets_list->begin : NULL;
	while (ml)
	{
		mtmp = ml->next;
		if (ml->sectnunm == d->selected_sector && (ml->is_select = 1))
			delete_monster(d, d->interface.monster_list);
		ml = mtmp;
	}
	while (al)
	{
		atmp = al->next;
		if (al->sectnunm == d->selected_sector && (al->is_select = 1))
			delete_asset(d, d->interface.assets_list, NULL, NULL);
		al = atmp;
	}
}

/*
**	add_wall(d); // first wall
**	add_wall(d); // current wall
*/

void		add_sector(t_data *d)
{
	d->sectordrawing = true;
	d->numsectors++;
	d->sectors[d->numsectors - 1].firstwallnum = d->numwalls;
	d->sectors[d->numsectors - 1].numwalls = 0;
	d->sectors[d->numsectors - 1].floorheight = 0;
	d->sectors[d->numsectors - 1].floorpicnum = d->default_floor_texture;
	d->sectors[d->numsectors - 1].ceilheight = 1;
	d->sectors[d->numsectors - 1].ceilpicnum = d->default_ceil_texture;
	d->sectors[d->numsectors - 1].light = 1.0;
	d->sectors[d->numsectors - 1].blinking = false;
	d->sectors[d->numsectors - 1].slope = 0;
	d->sectors[d->numsectors - 1].slope_orientation = 0;
	d->sectors[d->numsectors - 1].slopeceil = 0;
	d->sectors[d->numsectors - 1].slopeceil_orientation = 0;
	d->sectors[d->numsectors - 1].is_animatedslope = false;
	d->sectors[d->numsectors - 1].is_animatedslopeceil = false;
	d->sectors[d->numsectors - 1].outdoor = 0;
	d->sectors[d->numsectors - 1].is_finish = false;
	d->sectors[d->numsectors - 1].is_harmful = false;
	d->sectors[d->numsectors - 1].is_elevator = false;
	add_wall(d);
	add_wall(d);
}

void		del_sector(t_data *d, int16_t sectnum, t_sector *sect)
{
	int			w;
	int			s;
	int			n;

	if (sectnum < 0)
		return ;
	check_if_assets_inside_sector(d);
	d->numwalls -= sect->numwalls;
	w = sect->firstwallnum - 1;
	while (++w < d->numwalls)
	{
		d->walls[w] = d->walls[w + sect->numwalls];
		if (d->walls[w].neighborsect == sectnum)
			d->walls[w].neighborsect = -1;
		if (d->walls[w].neighborsect > sectnum)
			d->walls[w].neighborsect--;
	}
	d->numsectors--;
	s = sectnum - 1;
	n = sect->numwalls;
	while (++s < d->numsectors)
	{
		d->sectors[s] = d->sectors[s + 1];
		d->sectors[s].firstwallnum -= n;
	}
}

static bool	inside(t_data *d, int16_t sectnum, t_vec2f p)
{
	int		i;
	int		j;
	bool	c;
	t_vec2f	w0;
	t_vec2f	w1;

	c = 0;
	i = 0;
	j = d->sectors[sectnum].numwalls - 1;
	while (i < d->sectors[sectnum].numwalls)
	{
		w0 = d->walls[d->sectors[sectnum].firstwallnum + i].point;
		w1 = d->walls[d->sectors[sectnum].firstwallnum + j].point;
		if (((w0.y > p.y) != (w1.y > p.y)) &&
			(p.x < (w1.x - w0.x) * (p.y - w0.y) / (w1.y - w0.y) + w0.x))
			c = !c;
		j = i++;
	}
	return (c);
}

int16_t		find_sect_under_cursor(t_data *d)
{
	int		x;
	int		y;
	int		s;
	t_vec2f	p;

	SDL_GetMouseState(&x, &y);
	p = screentoworld(d, (t_vec2f){x, y});
	s = -1;
	while (++s < d->numsectors)
		if (inside(d, s, p))
			return (s);
	return (-1);
}
