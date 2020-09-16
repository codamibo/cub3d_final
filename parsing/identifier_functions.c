/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   identifier_functions.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/16 10:34:08 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:32:42 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

t_handler g_identifier_funs[8] = {path, path, path, path, path, res, col, col};

/*
** str is needed for file exist check
** first image pointer saved
** str freed in case of return in next statement
** address is saved
** else file not found
** if we're not at the newline after skip char&spaces
** -> too many arguments for element
*/

int		path(char *buf, int *i, t_vars *vars, int len)
{
	char	*str;
	int		end_spaces;

	skip_spaces(buf, i, len);
	end_spaces = count_end_spaces(buf, i, len);
	str = malloc((len - *i - end_spaces + 1) * sizeof(char));
	ft_strlcpy(str, &(buf[*i]), len - *i - end_spaces + 1);
	if (file_exists(str, vars) == -1)
	{
		if (str)
			free(str);
		parse_return(vars, "Error:\nUnable to open file of element: ", 2);
	}
	file_to_image(vars, str);
	if (str)
		free(str);
	if (vars->game.textures[vars->type].img == 0)
		parse_return(vars, "Error:\nUnable to open file of element: ", 2);
	get_addr(vars);
	while (buf[*i])
		(*i)++;
	if (*i == len)
		return (0);
	return (-1);
}

void	resize(t_vars *vars, int width, int height)
{
	int		reso_x;
	int		reso_y;

	mlx_get_screen_size(vars->mlx, &reso_x, &reso_y);
	if (width < 0 && vars->argc != 3)
		width = reso_x;
	if (height < 0 && vars->argc != 3)
		height = reso_y;
	if (vars->argc != 3)
		vars->image[0].img_width = (width > reso_x) ? reso_x : width;
	else if ((width < 0 || width > BMP_MAX) && vars->argc == 3)
		parse_return(vars, "Error:\nMaximum BMP width is 16384\n", 1);
	else
		vars->image[0].img_width = width;
	vars->image[1].img_width = vars->image[0].img_width;
	if (vars->argc != 3)
		vars->image[0].img_height = (height > reso_y) ? reso_y : height;
	else if ((height < 0 || height > BMP_MAX) && vars->argc == 3)
		parse_return(vars, "Error:\nMaximum BMP height is 16384\n", 1);
	else
		vars->image[0].img_height = height;
	if (width == 0 || height == 0)
		parse_return(vars, "Error:\nResolution must be > 0\n", 1);
	vars->image[1].img_height = vars->image[0].img_height;
}

int		res(char *buf, int *i, t_vars *vars, int len)
{
	int		width;
	int		height;

	skip_spaces(buf, i, len);
	if (ft_isdigit(buf[*i]))
		width = ft_atoi(&(buf[*i]));
	skip_digits(buf, i, len);
	skip_spaces(buf, i, len);
	if (ft_isdigit(buf[*i]))
		height = ft_atoi(&(buf[*i]));
	else
		parse_return(vars, "Error:\nWrong arguments for element: ", 2);
	resize(vars, width, height);
	skip_digits(buf, i, len);
	skip_spaces(buf, i, len);
	if (*i == len)
		return (0);
	return (-1);
}

/*
** first digit is always red, then green then blue
** these numbers have to be in between 0 and 255 before trgb can be created
** this is checked in save_col()
*/

int		col(char *buf, int *i, t_vars *vars, int len)
{
	int r;
	int g;
	int b;

	skip_spaces(buf, i, len);
	r = (ft_isdigit(buf[*i])) ? ft_atoi(&(buf[*i])) : -1;
	skip_digits(buf, i, len);
	skip_spaces(buf, i, len);
	(*i) = (buf[*i] == ',') ? (*i) + 1 : (*i);
	skip_spaces(buf, i, len);
	g = (ft_isdigit(buf[*i])) ? ft_atoi(&(buf[*i])) : -1;
	skip_digits(buf, i, len);
	skip_spaces(buf, i, len);
	(*i) = (buf[*i] == ',') ? (*i) + 1 : (*i);
	skip_spaces(buf, i, len);
	b = (ft_isdigit(buf[*i])) ? ft_atoi(&(buf[*i])) : -1;
	skip_digits(buf, i, len);
	skip_spaces(buf, i, len);
	save_col(r, g, b, vars);
	if (*i != len)
		return (-1);
	return (0);
}

int		identifier_functions(char *buf, int *i, t_vars *vars, int len)
{
	return (g_identifier_funs[vars->type](buf, i, vars, len));
}
