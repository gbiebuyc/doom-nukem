// 2 first octets, check if valid BMP
// SKIP 16 octets
// read 2 ints, width then height
// skip 2 octet
// bpp 2o
// skip 24o
#include "editor.h"
#include "bmp_reader.h"

int		bmp_reader(t_data *d)
{
	int		fd;
	t_bmp	bmp;
(void)d;
/**/	char *path = "./textures/a.bmp";
	if ((fd = open(path, O_RDONLY)) != -1)
	{
		if (read(fd, &bmp.header.signature, 2) < 0 ||
			read(fd, &bmp.header.filesize, 4) < 0 ||
			read(fd, &bmp.header.unused, 4) < 0 ||
			read(fd, &bmp.header.data_offset, 4) < 0 ||
			read(fd, &bmp.header.sizeinfoheader, 4) < 0 ||
			read(fd, &bmp.header.width, 4) < 0 ||
			read(fd, &bmp.header.height, 4) < 0 ||
			read(fd, &bmp.header.planes, 2) < 0 ||
			read(fd, &bmp.header.bpp, 2) < 0 ||
			read(fd, &bmp.header.compression, 4) < 0 ||
			read(fd, &bmp.header.imageSize, 4) < 0 ||
			read(fd, &bmp.header.x_pixels_per_m, 4) < 0 ||
			read(fd, &bmp.header.y_pixels_per_m, 4) < 0 ||
			read(fd, &bmp.header.colors_used, 4) < 0 ||
			read(fd, &bmp.header.important_colors, 4) < 0 ||
			read(fd, &bmp.header.rgba, 4) < 0)

			return (ft_printf("Failed to read\n"));
		
		int i = 0;
		ft_printf("sig : ");
		while (i < 2)
			ft_printf("%c", bmp.header.signature[i++]);
		ft_printf("\nfielsize : %d\n", bmp.header.filesize);
		ft_printf("unused : %d\n", bmp.header.unused);
		ft_printf("Offset : %x\n", bmp.header.data_offset);
		ft_printf("sizeheader : %d\n", bmp.header.sizeinfoheader);
		ft_printf("width : %d\n", bmp.header.width);
		ft_printf("height : %d\n", bmp.header.height);
		ft_printf("planes : %d\n", bmp.header.planes);
		ft_printf("bpp : %d\n", bmp.header.bpp);
		ft_printf("compression : %d", bmp.header.compression); (bmp.header.compression == 0) ? ft_printf("\tNo compression\n") : ft_printf("\tCompressed !!!\n");
		ft_printf("image size (octets) : %d\n", bmp.header.imageSize);
		ft_printf("x_pixels_per_m : %d\n", bmp.header.x_pixels_per_m);
		ft_printf("y_pixels_per_m : %d\n", bmp.header.y_pixels_per_m);
		ft_printf("color_used : %d\n", bmp.header.colors_used);
		(bmp.header.important_colors == 0) ? ft_printf("imortant color : all\n") : ft_printf("imortant color : %d\n", bmp.header.colors_used);
		//ft_printf("pixels format : %x %x %x %x", bmp.header.r, bmp.header.g, bmp.header.b, bmp.header.a);
		ft_printf("pixels format : %x\n", bmp.header.rgba);
		close(fd);
		

		if ((fd = open(path, O_RDONLY)) != -1)
		{
			char *data;
			SDL_Surface	*texture_test;

			data = (char*)malloc(bmp.header.filesize);
			if (read(fd, data, bmp.header.filesize) < 0)
				return (ft_printf("Failed to get data.\n"));
			ft_printf("%c%c\n", data[0], data[1]);

			texture_test = SDL_CreateRGBSurfaceWithFormat(0, bmp.header.width,
                                            bmp.header.height, 32,
                                            d->screen->format->format);
			int o = bmp.header.filesize - bmp.header.imageSize;
			int size = bmp.header.filesize - o - 1;
		/*	while (size >= o)
			{
				((char*)texture_test->pixels)[size] = data[size];
				size--;
			}*/

			ft_memcpy(texture_test->pixels, &data[o], size);
			copy_surface_to_surface(texture_test, d->screen, (int[2]){0,0}, d);
		}
	}
	else
		return (ft_printf("Failed ot open bmp file.\n"));
	return (0);
}
