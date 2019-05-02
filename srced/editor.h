/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 05:06:40 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/02 21:40:32 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include <common.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdint.h>
# include <fcntl.h>

# define W 1500
# define H 1000
# define MAXNUMSECTORS 1024
# define MAXNUMWALLS 8192
# define GRIDSIZE 64

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
	t_wall			*selectedwall;
	t_wall			*selectedwall2;
}					t_data;

extern char **environ; // used by execve

void	run_game();
void	init_sdl(t_data *d);
void	main_loop(t_data *d);
void	draw_screen(t_data *d);
void	init_sectors(t_data *d);
void	save_file(t_data *d);
void	create_sector(t_data *d);
void	putpixel(t_data *d, int x, int y, uint32_t color);
void	draw_grid(t_data *d);
void	draw_line(t_data *d, t_vec2f v1, t_vec2f v2, uint32_t color);
void	draw_sector(t_data *d, int16_t sectnum);
t_vec2f	worldtoscreen(t_data *d, t_vec2f p);
t_vec2f	screentoworld(t_data *d, t_vec2f p);
void	select_wall_under_cursor(t_data *d, t_vec2f p);
void	update_pos(t_data *d, t_vec2f p);
void	update_wall_pos(t_data *d, t_vec2f v);

#endif
