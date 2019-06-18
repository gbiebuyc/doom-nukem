/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_save_posters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 20:30:09 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/18 20:30:10 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		write_posters_data(t_data *d, int f)
{
	int				i;

	if (write(f, &d->nb_posters, sizeof(int32_t)) < 0)
		return (ft_printf("Error write nb posters.\n"));
	i = -1;
	while (++i < d->nb_posters)
	{
		if (write(f, &d->posters[i]->w, sizeof(int)) < 0 ||
			write(f, &d->posters[i]->h, sizeof(int)) < 0 ||
			write(f, d->posters[i]->pixels, 4 * (d->posters[i]->w *
												d->posters[i]->h)) < 0)
			return (ft_printf("Failed to write texture data.\n"));
	}
	return (0);
}
