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

void	draw_char(t_data *d, char c, int x, int y, uint32_t color)
{
	int i,j;

	// Convert the character to an index
	c = c & 0x7F;
	if (c < ' ')
		c = 0;
	else
		c -= ' ';
	const uint8_t* chr = d->font[(int)c];
	// Draw pixels
	for (j=0; j<CHAR_WIDTH; j++) {
		for (i=0; i<CHAR_HEIGHT; i++) {
			if (chr[j] & (1<<i))
				putpixel(d, x+j, y+i, color);
		}
	}
}

void	draw_string(t_data *d, const char* str, int x, int y, uint32_t color)
{
	while (*str) {
		draw_char(d, *str++, x, y, color);
		x += CHAR_WIDTH + 1;
	}
}

/*
void	init_font(t_data *d)
{
	d->font[0] = (unsigned char[5]){0x00,0x00,0x00,0x00,0x00};
}
*/
