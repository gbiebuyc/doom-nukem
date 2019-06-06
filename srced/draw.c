/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 11:15:00 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/04 12:27:14 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_screen(t_data *d)
{
	ft_memset(d->screen->pixels, 0, W * H * 4);
	draw_grid(d);
	for (int s = 0; s < d->numsectors; s++)
		draw_sector(d, s);
	SDL_UpdateWindowSurface(d->win);
}

void	draw_grid(t_data *d)
{
	int x;
	int y;

	for (int i = -GRIDSIZE; i <= GRIDSIZE; i++)
	{
		x = worldtoscreen(d, (t_vec2f){i, 0}).x;
		for (y = 0; y < H; y++)
			putpixel(d, x, y, 0x505050);
		y = worldtoscreen(d, (t_vec2f){0, i}).y;
		for (x = 0; x < W; x++)
			putpixel(d, x, y, 0x505050);
	}
}

void	draw_line(t_data *d, t_vec2f v1, t_vec2f v2, uint32_t color)
{
	t_vec2	delta;
	int		steps;
	t_vec2f	increment;

	delta.x = v2.x - v1.x;
	delta.y = v2.y - v1.y;
	steps = (abs(delta.x) > abs(delta.y)) ? abs(delta.x) : abs(delta.y);
	increment.x = delta.x / (double)steps;
	increment.y = delta.y / (double)steps;
	while (steps--)
	{
		putpixel(d, (int)v1.x, (int)v1.y, color);
		v1 = add_vec2f(v1, increment);
	}
}

void	draw_sector(t_data *d, int16_t sectnum)
{
	int i, j;

	int npoints = d->sectors[sectnum].numwalls;
	for (i = 0, j = npoints-1; i < npoints; j = i++)
	{
		t_wall *w0 = &d->walls[d->sectors[sectnum].firstwallnum + i];
		t_wall *w1 = &d->walls[d->sectors[sectnum].firstwallnum + j];
		t_vec2f p0 = worldtoscreen(d, w0->point);
		t_vec2f p1 = worldtoscreen(d, w1->point);
		// Draw walls in white and portals in red.
		draw_line(d, p0, p1, (w1->neighborsect != -1) ? 0xdd0000 : 0xffffff);
	}
}

t_vec2f	worldtoscreen(t_data *d, t_vec2f p)
{
	return ((t_vec2f){(p.x - d->pos.x) * d->scale + W / 2,
			-(p.y - d->pos.y) * d->scale + H / 2});
}

t_vec2f	screentoworld(t_data *d, t_vec2f p)
{
	return ((t_vec2f){(p.x - W / 2) / d->scale + d->pos.x,
			-(p.y - H / 2) / d->scale + d->pos.y});
}

t_vec2f	grid_lock(t_data *d, t_vec2f p)
{
	if (!d->grid_locking)
		return (p);
	return ((t_vec2f){floor(p.x + 0.5), floor(p.y + 0.5)});
}
