/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   screenshot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/25 14:13:19 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/06 13:55:38 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int		header(t_vars *vars, int fd)
{
	char	s[54];
	int		padding;

	padding = 0;
	ft_bzero(s, 54);
	s[0] = 0x42;
	s[1] = 0x4d;
	while ((3 * vars->image[vars->img_index].img_width + padding) % 4 != 0)
		padding++;
	s[2] = 3 * (vars->image[vars->img_index].img_width + padding) *
	vars->image[vars->img_index].img_height + 54;
	s[10] = 54;
	s[14] = 40;
	ft_memcpy(&s[18], &vars->image[vars->img_index].img_width, 4);
	ft_memcpy(&s[22], &vars->image[vars->img_index].img_height, 4);
	s[26] = 1;
	s[28] = 24;
	write(fd, s, 54);
	return (padding);
}

void	write_line(t_vars *vars, int fd, int len)
{
	int		x;
	char	*string;

	x = 0;
	while (x < vars->image[vars->img_index].img_width)
	{
		string = (vars->image[vars->img_index].addr + (len *
		vars->image[vars->img_index].line_length + x *
		(vars->image[vars->img_index].bits_per_pixel / 8)));
		x++;
		write(fd, string, 3);
	}
}

int		screenshot(t_vars *vars)
{
	int fd;
	int padding;
	int len;

	fd = open("cub3d.bmp", O_RDWR | O_CREAT, 0666);
	padding = header(vars, fd);
	len = vars->image[vars->img_index].img_height - 1;
	while (len >= 0)
	{
		write_line(vars, fd, len);
		write(fd, "\0\0\0", padding);
		len--;
	}
	close(fd);
	free_arrays(vars);
	exit(0);
	return (0);
}
