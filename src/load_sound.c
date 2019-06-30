/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 00:10:57 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/30 18:52:45 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		load_sound2(t_data *d, int f)
{
	static int	i;
	uint8_t		*tmp_file;
	int			size_of_file;
	SDL_RWops	*rw;

	if (read(f, &size_of_file, sizeof(int)) < 0)
		return (ft_printf("Failed to read size of sound_file\n"));
	printf("%d\n", size_of_file);
	if (!(tmp_file = malloc(size_of_file)))
		return (ft_printf("Failed to malloc sound\n"));
	if (read(f, tmp_file, size_of_file) < 0)
		return (ft_printf("Failed to read sound file\n"));
	if (!(rw = SDL_RWFromMem(tmp_file, size_of_file)))
		return (ft_printf("failed to init rw: %s\n", SDL_GetError()));
	if (!(d->chunk[i] = Mix_LoadWAV_RW(rw, 1)))
		return (ft_printf("Failed to initialize chunk with Mix\n"));
	free(tmp_file);
	i++;
	return (0);
}

int		load_sound(t_data *d, int f)
{
	short	i;

	i = 0;
	if (d->chunk[0])
		return (0);
	while (i++ < NB_OF_SOUNDS)
		if (load_sound2(d, f))
			return (1);
	return (0);
}
