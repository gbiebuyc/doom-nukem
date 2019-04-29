/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 05:06:40 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/29 09:11:33 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include <SDL.h>
# include <common_structs.h>
# include <libft.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdint.h>
# include <fcntl.h>

# define W 800
# define H 600
# define MAXNUMSECTORS 1024
# define MAXNUMWALLS 8192

typedef struct		s_data
{
	SDL_Window		*win;
	SDL_Surface		*screen;
	SDL_Surface		*textures[4];
	double			scale;
	t_vec2f			pos;
	t_sector		sectors[MAXNUMSECTORS];
	t_wall			walls[MAXNUMWALLS];
	int16_t			numsectors;
	int16_t			numwalls;
}					t_data;

extern char **environ; // used by execve

void	run_game();
void	init_sdl(t_data *d);
void	main_loop(t_data *d);
void	draw_screen(t_data *d);
void	init_sectors(t_data *d);
void	save_file(t_data *d);
void	create_sector(t_data *d);

#endif
