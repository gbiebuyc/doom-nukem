/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 11:15:00 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/08 16:15:39 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_line(t_data *d, t_vec2f v1, t_vec2f v2, uint32_t color)
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
		if (d->interface.texture_case_select == -1 &&
			(int)v1.x < W - PROPERTIES_LIMIT)
			putpixel(d, (int)v1.x, (int)v1.y, color);
		else if ((int)v1.x < W - TEXTURE_TOOLBAR)
			putpixel(d, (int)v1.x, (int)v1.y, color);
		v1 = add_vec2f(v1, increment);
	}
}

/*
**	Draw walls in white and portals in red.
*/

static void	draw_sector(t_data *d, int16_t sectnum)
{
	int		i;
	int		j;
	t_vec2f	p[2];
	t_wall	*w[2];

	i = 0;
	j = d->sectors[sectnum].numwalls - 1;
	while (i < d->sectors[sectnum].numwalls)
	{
		w[0] = &d->walls[d->sectors[sectnum].firstwallnum + i];
		w[1] = &d->walls[d->sectors[sectnum].firstwallnum + j];
		p[0] = worldtoscreen(d, w[0]->point);
		p[1] = worldtoscreen(d, w[1]->point);
		if (d->sectors[sectnum].firstwallnum + j == d->hl_wallnum_draw)
			draw_line(d, p[0], p[1], 0xffff00);
		else
			draw_line(d, p[0], p[1],
				w[1]->neighborsect != -1 ? 0xdd0000 : 0xffffff);
		j = i++;
	}
}

static void	draw_grid(t_data *d)
{
	int	x;
	int	y;
	int	i;
	int	limit;

	i = -GRIDSIZE;
	limit = W - (d->interface.texture_case_select != -1 ? TEXTURE_TOOLBAR
														: PROPERTIES_LIMIT);
	while (i++ <= GRIDSIZE)
	{
		x = worldtoscreen(d, (t_vec2f){i, 0}).x;
		y = 0;
		while (y++ < H)
			if (x < limit)
				putpixel(d, x, y, 0x505050);
		y = worldtoscreen(d, (t_vec2f){0, i}).y;
		x = 0;
		while (x++ < limit)
			putpixel(d, x, y, 0x505050);
	}
}

void		draw_screen(t_data *d)
{
	int	s;

	ft_memset(d->screen->pixels, 0, W * H * 4);
	draw_grid(d);
	s = -1;
	while (++s < d->numsectors)
		draw_sector(d, s);
	draw_assets_to_map(d, d->interface.toolbar.assets);
	show_menu(d);
	if (d->interface.category != -1)
		draw_selection_arround_asset(d, d->interface.category_pos);
	if (d->interface.selected_asset != -1)
		draw_selection_arround_selected_asset(d,
						&d->interface.selected_asset_position, 0x00ff00);
/********** test */

// int n;
// 	int i = -1;
// 	int x = 0;
// 	int y = 20;
// static int check = 1;

// n = 0;
// while (n < 1) //  modify 1 only if more assets
// {
// 	if (check)
// {
// 	check = 0;
// 	ft_printf("nb walk anim = %d\n", d->texture_monster[n].nb_walk_anim);
// 	ft_printf("nb walk orientation = %d\n", d->texture_monster[n].nb_walk_orientation);
// 	ft_printf("nb attack anim = %d\n", d->texture_monster[n].nb_attack_anim);
// 	ft_printf("nb attack orientation = %d\n", d->texture_monster[n].nb_attack_orientation);
// 	ft_printf("nb death anim = %d\n", d->texture_monster[n].nb_death_anim);
// }
// 	while (++i < d->texture_monster[n].nb_walk_anim)
// 	{
// 		if (i % 5 == 0)
// 		{
// 			x = 0;
// 			y += x+=d->texture_monster[n].walk[i]->h;
// 		}
// 		copy_surface_to_surface(d->texture_monster[0].walk[i], d->screen,
// 							(int[2]){x, y}, d);
// 		x += d->texture_monster[0].walk[i]->w;
// 	}
// 	i = -1;
// 	x = 0;
// 	y = 500;
// 	while (++i < d->texture_monster[n].nb_attack_anim)
// 	{
// 		if (i % 5 == 0)
// 		{
// 			x = 0;
// 			y += x+=d->texture_monster[n].attack[i]->h;
// 		}
// 		copy_surface_to_surface(d->texture_monster[n].attack[i], d->screen,
// 							(int[2]){x, y}, d);
// 		x += d->texture_monster[0].attack[i]->w;
// 	}

// 	i = -1;
// 	x = 100;
// 	y = 1000;
// 	while (++i < d->texture_monster[n].nb_death_anim)
// 	{
// 		copy_surface_to_surface(d->texture_monster[n].death[i], d->screen,
// 							(int[2]){x, y}, d);
// 		x += d->texture_monster[0].death[i]->w;
// 	}
// 	n++;
// }

/**************** */
///**/bmp_reader(d);
	SDL_UpdateWindowSurface(d->win);
}
