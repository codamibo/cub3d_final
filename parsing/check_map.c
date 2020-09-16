/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/31 15:22:03 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/06 12:05:39 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

/*
** Function is called in parse to check wheter all 8 elements are found,
** this is checked while parsing a line, and saved in the array elem_found
*/

int		all_elem_found(t_info *map)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (map->elem_found[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

/*
** Recusive function: calls itself whenever it is not at a wall,
** in all its directions, when it is at a wall, it returns 0 --> next
** thing on stack will be handled. If it can ever be at the borders
** of the map, without it being a 1, player is not surrounded by walls
*/

int		flood_fill(int x, int y, t_vars *vars)
{
	if (vars->map.array_copy[y][x] != 1 &&
	(x == 0 || x == vars->map.xmax - 1 || y == 0 || y == vars->map.ymax - 1))
		parse_return(vars, "Error:\nPlayer is not surrounded by walls\n", 1);
	if (vars->map.array_copy[y][x] != 1)
	{
		vars->map.array_copy[y][x] = 1;
		if (flood_fill(x, y + 1, vars))
			return (1);
		if (flood_fill(x, y - 1, vars))
			return (1);
		if (flood_fill(x + 1, y, vars))
			return (1);
		if (flood_fill(x - 1, y, vars))
			return (1);
		if (flood_fill(x + 1, y - 1, vars))
			return (1);
		if (flood_fill(x + 1, y + 1, vars))
			return (1);
		if (flood_fill(x - 1, y - 1, vars))
			return (1);
		if (flood_fill(x - 1, y + 1, vars))
			return (1);
	}
	return (0);
}

/*
** Function exits when player is not surrounded by walls or multiple or
** none start characters are present
*/

void	check_map(t_vars *vars)
{
	if (flood_fill(vars->map.xstart, vars->map.ystart, vars))
		parse_return(vars, "", 0);
	if (vars->map.multiple_start_char == 1)
		parse_return(vars, "Error:\nMultiple starting characters in map\n", 1);
	if (vars->map.start_char == 'x')
		parse_return(vars, "Error:\nStarting character is missing\n", 1);
}
