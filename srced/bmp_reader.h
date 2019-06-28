/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_reader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 13:10:25 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/28 13:10:26 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_READER_H
# define BMP_READER_H

# include <stdint.h>

typedef struct	s_header
{
	char		signature[2];
	int32_t		filesize;
	int32_t		unused;
	int32_t		data_offset;
	int32_t		sizeinfoheader;
	int32_t		width;
	int32_t		height;
	int16_t		planes;
	int16_t		bpp;
	int32_t		compression;
	int32_t		imagesize;
	int32_t		x_pixels_per_m;
	int32_t		y_pixels_per_m;
	int32_t		colors_used;
	int32_t		important_colors;
	int32_t		rgba;
}				t_header;

typedef struct	s_bmp
{
	t_header		header;
	unsigned char	*pixels;
}				t_bmp;

#endif
