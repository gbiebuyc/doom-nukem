#ifndef BMP_READER
# define BMP_READER

#include <stdint.h>

// bpp
// 1 = monochrome palette. NumColors = 1   
// 4 = 4bit palletized. NumColors = 16   
// 8 = 8bit palletized. NumColors = 256  
// 16 = 16bit RGB. NumColors = 65536
// 24 = 24bit RGB. NumColors = 16M

// compression
// 0 = BI_RGB   no compression   
// 1 = BI_RLE8 8bit RLE encoding   
// 2 = BI_RLE4 4bit RLE encoding

typedef struct s_header
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
	int32_t		imageSize;
	int32_t		x_pixels_per_m;
	int32_t		y_pixels_per_m;
	int32_t		colors_used;
	int32_t		important_colors;
	
	int32_t		rgba;
/*	int8_t		r;
	int8_t		g;
	int8_t		b;
	int8_t		a;*/
}               t_header;

typedef struct	s_bmp
{
	t_header		header;
	unsigned char	*pixels;
}				t_bmp;

#endif