/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 00:10:07 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/24 00:10:07 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	invoke_msg(t_data *d, char *msg)
{
	if (ft_strlen(msg) > 99)
		return ((void)ft_printf("msg is too long\n"));
	ft_strcpy(d->msg, msg);
	d->msg_start = SDL_GetTicks();
}
