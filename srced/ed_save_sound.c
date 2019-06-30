/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_write_sound.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:55:56 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/30 17:52:10 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		write_sound2(int f, char *path)
{
	Mix_Chunk			*chunk;

	if (!(chunk = Mix_LoadWAV(path)))
		return (ft_printf("Could not open wav file: %s\n", SDL_GetError()));
	if (write(f, &chunk->alen, sizeof(chunk->alen)) < 0)
		return (ft_printf("Failed to write wav spec.\n"));
	if (write(f, chunk->abuf, chunk->alen) < 0)
		return (ft_printf("Failed to write abuf \n"));
	Mix_FreeChunk(chunk);
	return (0);
}

int		write_sound(int f)
{
	if (write_sound2(f, "./sounds/music.wav") ||
			write_sound2(f, "./sounds/blaster.wav") ||
			write_sound2(f, "sounds/cryo_bal.wav") ||
			write_sound2(f, "sounds/m16.wav") ||
			write_sound2(f, "sounds/explosion.wav") ||
			write_sound2(f, "sounds/player_fell.wav") ||
			write_sound2(f, "sounds/player_got_hit.wav") ||
			write_sound2(f, "sounds/player_death.wav") ||
			write_sound2(f, "sounds/charg_agro.wav") ||
			write_sound2(f, "sounds/charg_damage.wav") ||
			write_sound2(f, "sounds/charg_death.wav") ||
			write_sound2(f, "sounds/mother_agro.wav") ||
			write_sound2(f, "sounds/mother_attack.wav") ||
			write_sound2(f, "sounds/mother_death.wav") ||
			write_sound2(f, "sounds/blaster_2.wav") ||
			write_sound2(f, "sounds/refill_ammo.wav") ||
			write_sound2(f, "sounds/health_up.wav") ||
			write_sound2(f, "sounds/door_open.wav") ||
			write_sound2(f, "sounds/door_close.wav"))
		return (1);
	return (0);
}
