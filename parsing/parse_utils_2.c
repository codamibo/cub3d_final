/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils_2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/16 10:22:21 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/06 15:49:24 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int		count_end_spaces(char *buf, int *i, int len)
{
	int spaces;

	spaces = 0;
	while (buf[len - spaces - 1] == ' ' && len > *i)
		spaces++;
	return (spaces);
}

void	file_to_image(t_vars *vars, char *str)
{
	if (vars->file_type == 0)
		vars->game.textures[vars->type].img = mlx_xpm_file_to_image(
		vars->mlx, str, &vars->game.textures[vars->type].img_width,
		&vars->game.textures[vars->type].img_height);
	else
		vars->game.textures[vars->type].img = mlx_png_file_to_image(
		vars->mlx, str, &vars->game.textures[vars->type].img_width,
		&vars->game.textures[vars->type].img_height);
}

int		file_exists(char *filename, t_vars *vars)
{
	int fd;
	int len;

	len = ft_strlen(filename);
	if (!((filename[len - 1] == 'm' && filename[len - 2] == 'p' &&
	filename[len - 3] == 'x' && filename[len - 4] == '.') ||
	(filename[len - 1] == 'M' && filename[len - 2] == 'P' &&
	filename[len - 3] == 'X' && filename[len - 4] == '.') ||
	(filename[len - 1] == 'g' && filename[len - 2] == 'n' &&
	filename[len - 3] == 'p' && filename[len - 4] == '.') ||
	(filename[len - 1] == 'G' && filename[len - 2] == 'N' &&
	filename[len - 3] == 'P' && filename[len - 4] == '.')))
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (filename[len - 3] == 'x' || filename[len - 3] == 'X')
		vars->file_type = 0;
	else
		vars->file_type = 1;
	close(fd);
	return (1);
}

void	get_addr(t_vars *vars)
{
	vars->game.textures[vars->type].addr =
	mlx_get_data_addr(vars->game.textures[vars->type].img,
	&vars->game.textures[vars->type].bits_per_pixel,
	&vars->game.textures[vars->type].line_length,
	&vars->game.textures[vars->type].endian);
	vars->game.textures[vars->type].int_addr =
	(int *)vars->game.textures[vars->type].addr;
}

void	clean_map(t_vars *vars)
{
	int		i;

	i = 0;
	vars->image[0].img_width = -1;
	vars->image[0].img_height = -1;
	vars->image[1].img_width = -1;
	vars->image[1].img_height = -1;
	vars->map.col_floor = -1;
	vars->map.col_ceiling = -1;
	vars->map.whole_map = ft_calloc(1, sizeof(char));
	vars->map.xmax = 0;
	vars->map.ymax = 0;
	vars->map.xstart = 0;
	vars->map.ystart = 0;
	vars->map.start_char = 'x';
	vars->map.num_sprites = 0;
	vars->map.start_char_found = 0;
	vars->map.multiple_start_char = 0;
	vars->map.empty_line = 0;
	while (i < 8)
	{
		vars->map.elem_found[i] = 0;
		i++;
	}
}
