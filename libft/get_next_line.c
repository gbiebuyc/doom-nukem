/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:46:06 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:25:22 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_file	*get_file(t_file **lst, int fd)
{
	t_file	*f;

	f = *lst;
	while (f)
	{
		if (f->fd == fd)
			return (f);
		f = f->next;
	}
	if (!(f = malloc(sizeof(t_file))))
		return (0);
	f->fd = fd;
	f->buf = 0;
	f->next = *lst;
	*lst = f;
	return (f);
}

static char		*find_eol(char *s)
{
	if (!s)
		return (0);
	return (ft_strchr(s, '\n'));
}

static int		push_buf(char **file_buf, char *read_buf)
{
	char	*to_free;

	if (!*file_buf)
	{
		if (!(*file_buf = ft_strdup(read_buf)))
			return (0);
	}
	else
	{
		to_free = *file_buf;
		if (!(*file_buf = ft_strjoin(*file_buf, read_buf)))
			return (0);
		free(to_free);
	}
	return (1);
}

static int		get_front_line(char **file_buf, char **line)
{
	char	*end_of_line;
	char	*to_free;

	if (!*file_buf || !**file_buf)
		return (0);
	if ((end_of_line = find_eol(*file_buf)))
	{
		if (!(*line = ft_strsub(*file_buf, 0, end_of_line - *file_buf)))
			return (0);
		to_free = *file_buf;
		if (!(*file_buf = ft_strdup(end_of_line + 1)))
			return (0);
		free(to_free);
	}
	else
	{
		if (!(*line = ft_strdup(*file_buf)))
			return (0);
		free(*file_buf);
		*file_buf = 0;
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char			read_buf[BUFF_SIZE + 1];
	char			*end_of_line;
	ssize_t			read_size;
	static t_file	*list;
	t_file			*file;

	if (fd < 0 || !line || !(file = get_file(&list, fd)))
		return (-1);
	end_of_line = find_eol(file->buf);
	read_size = 42;
	while (!end_of_line && read_size > 0)
	{
		read_size = read(fd, read_buf, BUFF_SIZE);
		if (read_size == -1)
			return (-1);
		read_buf[read_size] = '\0';
		if (!push_buf(&file->buf, read_buf))
			return (-1);
		end_of_line = find_eol(file->buf);
	}
	if (get_front_line(&file->buf, line))
		return (1);
	if (read_size == 0)
		return (0);
	return (-1);
}
