/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 16:17:46 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/05 20:14:00 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static int		read_fd(char **buf, int fd)
{
	int ret;
	int	buffer_size;

	buffer_size = 100;
	*buf = cal_loc((buffer_size + 1), sizeof(char));
	if (!*buf)
		return (-1);
	ret = read(fd, *buf, buffer_size);
	return (ret);
}

static int		return_value(int ret, int malloc_check, char **buf)
{
	if (ret == -1 || malloc_check == -1)
	{
		if (*buf)
		{
			free(*buf);
			*buf = NULL;
		}
		return (-1);
	}
	else if (ret == 0)
	{
		if (*buf)
		{
			free(*buf);
			*buf = NULL;
		}
		return (0);
	}
	else
		return (1);
}

static int		join(char **line, char **buf)
{
	*line = str_join(*line, *buf);
	if (*buf)
		free(*buf);
	*buf = NULL;
	if (!*line)
		return (-1);
	return (0);
}

static int		join_and_save(char **line, char **buf)
{
	int		i;
	char	*tmp;
	char	*end;

	i = 0;
	while ((*buf)[i] != '\n')
		i++;
	end = sub_str(*buf, 0, i);
	if (!end)
		return (-1);
	*line = str_join(*line, end);
	free(end);
	tmp = sub_str(*buf, i + 1, ft_strlen(*buf) - i);
	if (!tmp || !*line)
		return (-1);
	if (*buf)
		free(*buf);
	*buf = tmp;
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static char				*buf[FOPEN_MAX];
	int						ret;
	int						malloc_check;

	ret = 1;
	malloc_check = 0;
	if (fd < 0 || !line || read(fd, NULL, 0) < 0)
		return (-1);
	*line = cal_loc(1, sizeof(char));
	while (ret > 0 && *line)
	{
		if (buf[fd] == NULL)
			ret = read_fd(&buf[fd], fd);
		if (buf[fd] && !str_chr(buf[fd], '\n') && ret > 0)
			malloc_check = join(line, &buf[fd]);
		else if (buf[fd] && str_chr(buf[fd], '\n') && ret > 0)
		{
			malloc_check = join_and_save(line, &buf[fd]);
			return (return_value(ret, malloc_check, &buf[fd]));
		}
		if (malloc_check == -1 || ret <= 0)
			return (return_value(ret, malloc_check, &buf[fd]));
	}
	return (return_value(ret, -1, &buf[fd]));
}
