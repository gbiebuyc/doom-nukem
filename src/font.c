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

#include "doom_nukem.h"
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

#define C0 {0x00,0x00,0x00,0x00,0x00},{0x00,0x00,0xbe,0x00,0x00}
#define C1 {0x00,0x07,0x00,0x07,0x00},{0x48,0xfc,0x48,0xfc,0x48}
#define C2 {0x48,0x54,0xfe,0x54,0x24},{0x88,0x54,0x28,0x50,0xa8}
#define C3 {0x6c,0x92,0x92,0xac,0x40},{0xa0,0x00,0x07,0x00,0x00}
#define C4 {0x00,0x7c,0x82,0x01,0x00},{0x00,0x01,0x82,0x7c,0x00}
#define C5 {0x28,0x10,0x7c,0x10,0x28},{0x10,0x10,0x7c,0x10,0x10}
#define C6 {0x00,0x00,0x80,0x00,0x00},{0x10,0x10,0x10,0x10,0x10}
#define C7 {0x00,0x00,0x80,0x00,0x00},{0x00,0xc0,0x30,0x0c,0x03}
#define C8 {0x7c,0x82,0x92,0x82,0x7c},{0x00,0x84,0xfe,0x80,0x00}
#define C9 {0xc4,0xa2,0x92,0x92,0x8c},{0x44,0x82,0x92,0x92,0x6c}
#define C10 {0x30,0x28,0x24,0xfe,0x20},{0x5e,0x92,0x92,0x92,0x62}
#define C11 {0x78,0x94,0x92,0x92,0x60},{0x02,0x82,0x62,0x1a,0x06}
#define C12 {0x6c,0x92,0x92,0x92,0x6c},{0x0c,0x92,0x92,0x52,0x3c}
#define C13 {0x00,0x00,0x48,0x00,0x00},{0x00,0x80,0x48,0x00,0x00}
#define C14 {0x10,0x10,0x28,0x28,0x44},{0x28,0x28,0x28,0x28,0x28}
#define C15 {0x44,0x28,0x28,0x10,0x10},{0x04,0x02,0xa2,0x12,0x0c}
#define C16 {0x7c,0x82,0xba,0xba,0xa2},{0xfc,0x38,0x26,0x38,0xc0}
#define C17 {0xfe,0x92,0x92,0x92,0x6c},{0x7c,0x82,0x82,0x82,0x44}
#define C18 {0xfe,0x82,0x82,0x44,0x38},{0xfe,0x92,0x92,0x92,0x82}
#define C19 {0xfe,0x12,0x12,0x12,0x02},{0x7c,0x82,0x82,0x92,0xf4}
#define C20 {0xfe,0x10,0x10,0x10,0xfe},{0x00,0x82,0xfe,0x82,0x00}
#define C21 {0x80,0x80,0x82,0x82,0x7e},{0xfe,0x10,0x28,0x44,0x82}
#define C22 {0xfe,0x80,0x80,0x80,0x80},{0xfe,0x18,0x60,0x18,0xfe}
#define C23 {0xfe,0x06,0x38,0xc0,0xfe},{0x7c,0x82,0x82,0x82,0x7c}
#define C24 {0xfe,0x12,0x12,0x12,0x0c},{0x7c,0x82,0x82,0xc2,0xfc}
#define C25 {0xfe,0x12,0x12,0x12,0xec},{0x4c,0x92,0x92,0x92,0x64}
#define C26 {0x02,0x02,0xfe,0x02,0x02},{0x7e,0x80,0x80,0x80,0x7e}
#define C27 {0x0e,0x30,0xc0,0x30,0x0e},{0x1e,0xe0,0x1c,0xe0,0x1e}
#define C28 {0xc6,0x28,0x10,0x28,0xc6},{0x0e,0x10,0xf0,0x10,0x0e}
#define C29 {0xc2,0xa2,0x92,0x8a,0x86},{0x00,0xff,0x01,0x01,0x00}
#define C30 {0x03,0x0c,0x30,0xc0,0x00},{0x00,0x01,0x01,0xff,0x00}
#define C31 {0x08,0x04,0x02,0x04,0x08},{0x00,0x00,0x00,0x00,0x00}
#define C32 {0x00,0x00,0x02,0x04,0x00},{0x40,0xa8,0xa8,0xa8,0xf0}
#define C33 {0xff,0x88,0x88,0x88,0x70},{0x70,0x88,0x88,0x88,0x88}
#define C34 {0x70,0x88,0x88,0x88,0xff},{0x70,0xa8,0xa8,0xa8,0xb0}
#define C35 {0x08,0xfe,0x09,0x09,0x01},{0x70,0x88,0x88,0x88,0xf0}
#define C36 {0xff,0x08,0x08,0x08,0xf0},{0x00,0x08,0xfa,0x00,0x00}
#define C37 {0x00,0x00,0x08,0xfa,0x00},{0x00,0xff,0x20,0x50,0x88}
#define C38 {0x00,0x01,0xff,0x00,0x00},{0xf8,0x08,0xf0,0x08,0xf0}
#define C39 {0xf8,0x08,0x08,0x08,0xf0},{0x70,0x88,0x88,0x88,0x70}
#define C40 {0xf8,0x88,0x88,0x88,0x70},{0x70,0x88,0x88,0x88,0xf8}
#define C41 {0xf8,0x10,0x08,0x08,0x10},{0x90,0xa8,0xa8,0xa8,0x48}
#define C42 {0x00,0x7e,0x88,0x88,0x80},{0x78,0x80,0x80,0x80,0xf8}
#define C43 {0x18,0x60,0x80,0x60,0x18},{0x38,0xc0,0x30,0xc0,0x38}
#define C44 {0x88,0x50,0x20,0x50,0x88},{0x78,0x80,0x80,0x80,0xf8}
#define C45 {0x88,0xc8,0xa8,0x98,0x88},{0x00,0x10,0xee,0x01,0x00}
#define C46 {0x00,0x00,0xff,0x00,0x00},{0x00,0x01,0xee,0x10,0x00}
#define C47 {0x20,0x10,0x10,0x20,0x20},{0x00,0x00,0x00,0x00,0x00}

void	init_font(t_data *d)
{
	*d = (t_data){.font = {C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11,
		C12, C13, C14, C15, C16, C17, C18, C19, C20, C21, C22, C23, C24, C25,
		C26, C27, C28, C29, C30, C31, C32, C33, C34, C35, C36, C37, C38, C39,
		C40, C41, C42, C43, C44, C45, C46, C47}};
}
