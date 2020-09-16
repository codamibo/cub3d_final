/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast_setup.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/18 11:53:11 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/06 14:33:32 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	west(t_vars *vars)
{
	vars->game.dir_x = -1;
	vars->game.dir_y = 0;
	vars->game.plane_x = 0;
	vars->game.plane_y = -0.66;
}

void	dirs(t_vars *vars)
{
	if (vars->map.start_char == 'N')
	{
		vars->game.dir_x = 0;
		vars->game.dir_y = -1;
		vars->game.plane_x = 0.66;
		vars->game.plane_y = 0;
	}
	else if (vars->map.start_char == 'E')
	{
		vars->game.dir_x = 1;
		vars->game.dir_y = 0;
		vars->game.plane_x = 0;
		vars->game.plane_y = 0.66;
	}
	else if (vars->map.start_char == 'S')
	{
		vars->game.dir_x = 0;
		vars->game.dir_y = 1;
		vars->game.plane_x = -0.66;
		vars->game.plane_y = 0;
	}
	else if (vars->map.start_char == 'W')
		west(vars);
}

void	raycast_setup(t_vars *vars)
{
	vars->img_index = 1;
	vars->game.pos_x = vars->map.xstart;
	vars->game.pos_y = vars->map.ystart;
	vars->game.side = -1;
	vars->game.wall_type = -1;
	vars->game.w = vars->image[vars->img_index].img_width;
	vars->game.h = vars->image[vars->img_index].img_height;
	vars->game.z_buffer = malloc(vars->image[vars->img_index].img_width *
	sizeof(double));
	dirs(vars);
	raycast(vars);
}
