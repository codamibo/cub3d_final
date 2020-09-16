/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/01 11:56:05 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/06 12:47:01 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int			rotate_right(t_vars *vars)
{
	double	olddir_x;
	double	oldplane_x;

	if (vars->hooks.r_arrow == 1)
	{
		olddir_x = vars->game.dir_x;
		vars->game.dir_x = vars->game.dir_x * cos(ROT_SPEED) -
		vars->game.dir_y * sin(ROT_SPEED);
		vars->game.dir_y = olddir_x * sin(ROT_SPEED) + vars->game.dir_y *
						cos(ROT_SPEED);
		oldplane_x = vars->game.plane_x;
		vars->game.plane_x = vars->game.plane_x * cos(ROT_SPEED) -
						vars->game.plane_y * sin(ROT_SPEED);
		vars->game.plane_y = oldplane_x * sin(ROT_SPEED) +
		vars->game.plane_y * cos(ROT_SPEED);
		return (1);
	}
	return (0);
}

int			rotate(t_vars *vars)
{
	double	olddir_x;
	double	oldplane_x;
	int		change;

	change = 0;
	if (move(vars))
		change = 1;
	if (vars->hooks.l_arrow == 1)
	{
		olddir_x = vars->game.dir_x;
		vars->game.dir_x = vars->game.dir_x * cos(-ROT_SPEED) -
						vars->game.dir_y * sin(-ROT_SPEED);
		vars->game.dir_y = olddir_x * sin(-ROT_SPEED) + vars->game.dir_y
						* cos(-ROT_SPEED);
		oldplane_x = vars->game.plane_x;
		vars->game.plane_x = vars->game.plane_x * cos(-ROT_SPEED) -
						vars->game.plane_y * sin(-ROT_SPEED);
		vars->game.plane_y = oldplane_x * sin(-ROT_SPEED) +
						vars->game.plane_y * cos(-ROT_SPEED);
		change = 1;
	}
	if (rotate_right(vars))
		change = 1;
	return (change);
}
