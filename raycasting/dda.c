/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/18 12:09:15 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/06 14:36:28 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	wall_type(t_vars *vars)
{
	if (vars->game.side == Y)
		vars->game.wall_type = (vars->game.pos_x <= vars->game.map_x) ? EA :
		WE;
	else
		vars->game.wall_type = (vars->game.pos_y >= vars->game.map_y) ? NO :
		SO;
}

void	dda(t_vars *vars)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (vars->game.side_dist_x < vars->game.side_dist_y)
		{
			vars->game.side_dist_x += vars->game.delta_dist_x;
			vars->game.map_x += vars->game.step_x;
			vars->game.side = Y;
		}
		else
		{
			vars->game.side_dist_y += vars->game.delta_dist_y;
			vars->game.map_y += vars->game.step_y;
			vars->game.side = X;
		}
		if ((vars->map.array)[vars->game.map_y][vars->game.map_x] == 1)
		{
			wall_type(vars);
			hit = 1;
		}
	}
}
