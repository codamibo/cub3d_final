/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils_3.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/25 14:24:36 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:37:49 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	print_element(t_vars *vars)
{
	if (vars->type == NO)
		ft_putstr_fd("NO\n", 1);
	if (vars->type == EA)
		ft_putstr_fd("EA\n", 1);
	if (vars->type == SO)
		ft_putstr_fd("SO\n", 1);
	if (vars->type == WE)
		ft_putstr_fd("WE\n", 1);
	if (vars->type == S)
		ft_putstr_fd("S\n", 1);
	if (vars->type == R)
		ft_putstr_fd("R\n", 1);
	if (vars->type == F)
		ft_putstr_fd("F\n", 1);
	if (vars->type == C)
		ft_putstr_fd("C\n", 1);
}

void	parse_return(t_vars *vars, char *error, int err)
{
	if (vars->map.whole_map)
		free(vars->map.whole_map);
	if (vars->map.array)
		free(vars->map.array);
	if (vars->map.array_copy)
		free(vars->map.array_copy);
	if (vars->fd && vars->fd != -1)
		close(vars->fd);
	if (err > 0)
		ft_putstr_fd(error, 1);
	if (err == 2)
		print_element(vars);
	exit(0);
}

int		save_col(int r, int g, int b, t_vars *vars)
{
	if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
	{
		if (vars->type == C)
			vars->map.col_ceiling = create_trgb(0, r, g, b);
		else
			vars->map.col_floor = create_trgb(0, r, g, b);
	}
	else
		parse_return(vars,
		"Error:\nSpecified color does not exist for element: ", 2);
	return (0);
}
