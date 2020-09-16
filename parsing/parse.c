/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/26 10:33:58 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:15:23 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int		identifier_type(char *buf, int i)
{
	if (buf[i] == 'R' && buf[i + 1] == ' ')
		return (R);
	if (buf[i] == 'N' && buf[i + 1] == 'O')
		return (NO);
	if (buf[i] == 'S' && buf[i + 1] == 'O')
		return (SO);
	if (buf[i] == 'W' && buf[i + 1] == 'E')
		return (WE);
	if (buf[i] == 'E' && buf[i + 1] == 'A')
		return (EA);
	if (buf[i] == 'S' && buf[i + 1] == ' ')
		return (S);
	if (buf[i] == 'F' && buf[i + 1] == ' ')
		return (F);
	if (buf[i] == 'C' && buf[i + 1] == ' ')
		return (C);
	return (-1);
}

int		save_identifier_types(char *buf, int *i, int len, t_vars *vars)
{
	vars->type = -1;
	vars->type = identifier_type(buf, (*i));
	if (vars->type == -1 && is_map_character(buf[(*i)]))
		return (1);
	else if (vars->type == -1)
		parse_return(vars, "Error:\nType identifier does not exist\n", 1);
	if (vars->map.elem_found[vars->type] == 0)
		vars->map.elem_found[vars->type] = 1;
	else
		parse_return(vars, "Error:\nMultiple elements of same type\n", 1);
	(*i) = (*i) + 2;
	if (identifier_functions(buf, i, vars, len) == -1)
		parse_return(vars, "Error:\nWrong arguments for element: ", 2);
	return (2);
}

int		parse_line(char *buf, t_vars *vars)
{
	int	i;
	int	ret;
	int len;

	i = 0;
	ret = 0;
	len = ft_strlen(buf);
	while (i < len && ret == 0)
	{
		if (buf[i] != ' ')
		{
			ret = save_identifier_types(buf, &i, len, vars);
			if (ret == 1)
				return (ret);
		}
		else
			i++;
	}
	return (0);
}

void	read_file(t_vars *vars)
{
	int		ret;
	char	*buf;
	int		map_started;
	int		error_save;

	ret = 1;
	map_started = 0;
	error_save = 0;
	while (ret > 0)
	{
		ret = get_next_line(vars->fd, &buf);
		if (ft_strlen(buf) > 0 && map_started == 0)
			map_started = parse_line(buf, vars);
		if (map_started == 1)
			error_save = save_map(buf, vars);
		if (buf)
			free(buf);
		if (error_save == -1)
			parse_return(vars, "Error:\nWrong character in map\n", 1);
	}
	if (map_started == 0)
		parse_return(vars, "Error:\nMap is missing\n", 1);
}

void	parse(char **argv, t_vars *vars, int argc)
{
	int		len;

	vars->argc = argc;
	len = ft_strlen(argv[1]);
	vars->fd = open(argv[1], O_RDONLY);
	clean_map(vars);
	if (!(argv[1][len - 1] == 'b' && argv[1][len - 2] == 'u' &&
	argv[1][len - 3] == 'c' && argv[1][len - 4] == '.') || vars->fd == -1)
		parse_return(vars, "Error:\nUnable to read file\n", 1);
	read_file(vars);
	if (make_map_array(&(vars->map), &(vars->map.array), 1) == -1 ||
	make_map_array(&(vars->map), &(vars->map.array_copy), 0) == -1)
		parse_return(vars, "Error:\nMalloc went wrong\n", 1);
	check_map(vars);
	close(vars->fd);
}
