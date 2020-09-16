/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_arrays.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 12:57:16 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/06 16:12:40 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	free_sprites(t_vars *vars)
{
	if (vars->game.z_buffer)
	{
		free(vars->game.z_buffer);
		vars->game.z_buffer = NULL;
	}
	if (vars->game.sprite)
	{
		free(vars->game.sprite);
		vars->game.sprite = NULL;
	}
	if (vars->game.sprite_order)
	{
		free(vars->game.sprite_order);
		vars->game.sprite_order = NULL;
	}
	if (vars->game.sprite_distance)
	{
		free(vars->game.sprite_distance);
		vars->game.sprite_distance = NULL;
	}
}

void	free_arrays_2(t_vars *vars)
{
	if (vars->map.array)
	{
		free(vars->map.array);
		vars->map.array = NULL;
	}
	if (vars->map.array_copy)
	{
		free(vars->map.array_copy);
		vars->map.array_copy = NULL;
	}
	if (vars->map.whole_map)
	{
		free(vars->map.whole_map);
		vars->map.whole_map = NULL;
	}
	free_sprites(vars);
}

int		free_arrays(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->map.ymax)
	{
		if ((vars->map.array)[i])
		{
			free((vars->map.array)[i]);
			vars->map.array[i] = NULL;
		}
		if ((vars->map.array_copy)[i])
		{
			free((vars->map.array_copy)[i]);
			vars->map.array_copy[i] = NULL;
		}
		i++;
	}
	free_arrays_2(vars);
	return (0);
}
