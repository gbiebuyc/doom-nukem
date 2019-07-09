/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 21:48:33 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/07/09 22:13:24 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#define CHAR_WIDTH 5
#define CHAR_HEIGHT 8

bool	is_special_char(char c)
{
	return (c == 'y' || c == 'p' || c == 'q' || c == ',');
}

void	draw_char(t_data *d, t_font *f)
{
	int		i;
	int		j;
	char	c;
	int		y;

	c = *f->str & 0x7F;
	if (c < ' ')
		c = 0;
	else
		c -= ' ';
	j = -1;
	while (++j < CHAR_WIDTH * f->scale)
	{
		i = -1;
		y = is_special_char(*f->str) ? 2 * f->scale : 0;
		while (++i < CHAR_HEIGHT * f->scale)
			if (d->font[(int)c][j / f->scale] & (1 << i / f->scale))
			{
				putpixel(d, f->x + j, f->y + i + y, f->color);
				putpixel(d, f->x + j, f->y + i + y + f->scale, 0x000000);
			}
	}
}

void	draw_string(t_data *d, t_font f)
{
	int			x_start;

	if (f.scale <= 0)
		return ((void)ft_printf("bad fond scale\n"));
	x_start = f.x;
	while (*f.str)
	{
		draw_char(d, &f);
		f.x += (CHAR_WIDTH + 1) * f.scale;
		f.str++;
		if (*f.str == '\n' && ((f.x = x_start) == x_start) && f.str++)
			f.y += (CHAR_HEIGHT + 10) * f.scale;
	}
}

void	handle_keypress(int *delay)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			exit(EXIT_SUCCESS);
		if ((e.type != SDL_KEYDOWN) || e.key.repeat)
			continue ;
		else if (e.key.keysym.sym == SDLK_RETURN)
			*delay = 0;
		else if (e.key.keysym.sym == SDLK_ESCAPE)
			*delay = 0;
	}
}

void	draw_string_typewriter_effect(t_data *d, t_font f)
{
	int			x_start;
	int			delay;

	if (f.scale <= 0)
		return ((void)ft_printf("bad font scale\n"));
	x_start = f.x;
	delay = 30;
	while (*f.str)
	{
		draw_char(d, &f);
		SDL_UpdateWindowSurface(d->win);
		f.x += (CHAR_WIDTH + 1) * f.scale;
		f.str++;
		if (*f.str == '\n' && ((f.x = x_start) == x_start) && f.str++)
			f.y += (CHAR_HEIGHT + 10) * f.scale;
		if (delay)
		{
			SDL_Delay(delay);
			handle_keypress(&delay);
		}
	}
}
