/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 21:48:33 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/08 00:17:33 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

#define CHAR_WIDTH 5
#define CHAR_HEIGHT 8

void	draw_char(t_data *d, t_font *f)
{
	int		i;
	int		j;
	char	c;

	c = *f->str & 0x7F;
	if (c < ' ')
		c = 0;
	else
		c -= ' ';
	j = -1;
	while (++j < CHAR_WIDTH * f->scale)
	{
		i = -1;
		while (++i < CHAR_HEIGHT * f->scale)
			if (d->font[(int)c][j / f->scale] & (1 << i / f->scale))
				putpixel(d, f->x + j, f->y + i, f->col);
	}
}

void	draw_string(t_data *d, t_font f)
{
	if (f.scale <= 0)
		return ((void)printf("bad fond scale\n"));
	while (*f.str)
	{
		draw_char(d, &f);
		f.x += (CHAR_WIDTH + 1) * f.scale;
		f.str++;
	}
}

void	init_font(t_data *d)
{
	*d = (t_data){.font = {C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11,
		C12, C13, C14, C15, C16, C17, C18, C19, C20, C21, C22, C23, C24, C25,
		C26, C27, C28, C29, C30, C31, C32, C33, C34, C35, C36, C37, C38, C39,
		C40, C41, C42, C43, C44, C45, C46, C47}};
}
