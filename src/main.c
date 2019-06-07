/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:39:11 by nallani           #+#    #+#             */
/*   Updated: 2019/06/06 20:18:14 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		main(int argc, char **argv)
{	
	t_data d;

	(void)argc;
	(void)argv;
	load_map(&d);
	init_sdl(&d);
	init_player(&d, &d.player);
	init_monsters(&d);
	init_projectiles(&d);
	loop(&d);
	return (0);//windows wont compile
}
