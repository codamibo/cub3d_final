/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/18 12:40:03 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/06 12:46:52 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

/*
** If s key pressed, checks whether movement is valid, updates position player
** Funciton returns 1 if position is updated, 0 otherwise.
*/

int		front(t_vars *vars)
{
	if (vars->hooks.w == 1)
	{
		if (vars->map.array[(int)(vars->game.pos_y + vars->game.dir_y *
		MOVE_SPEED)][(int)(vars->game.pos_x)] != 1 &&
		vars->map.array[(int)vars->game.pos_y]
		[(int)(vars->game.pos_x + vars->game.dir_x * MOVE_SPEED)] != 1)
		{
			vars->game.pos_x += vars->game.dir_x * MOVE_SPEED;
			vars->game.pos_y += vars->game.dir_y * MOVE_SPEED;
			return (1);
		}
	}
	return (0);
}

/*
** If a key pressed, checks whether movement is valid, updates position player
** Funciton returns 1 if position is updated, 0 otherwise.
*/

int		left(t_vars *vars)
{
	if (vars->hooks.a == 1)
	{
		if (vars->map.array[(int)(vars->game.pos_y - vars->game.dir_x *
		MOVE_SPEED)][(int)(vars->game.pos_x + vars->game.dir_y *
		MOVE_SPEED)] != 1)
		{
			vars->game.pos_x -= vars->game.plane_x * MOVE_SPEED;
			vars->game.pos_y -= vars->game.plane_y * MOVE_SPEED;
			return (1);
		}
	}
	return (0);
}

/*
** If s key pressed, checks whether movement is valid, updates position player
** Funciton returns 1 if position is updated, 0 otherwise.
*/

int		back(t_vars *vars)
{
	if (vars->hooks.s == 1)
	{
		if (vars->map.array[(int)(vars->game.pos_y - vars->game.dir_y *
		MOVE_SPEED)][(int)vars->game.pos_x] != 1 &&
		vars->map.array[(int)vars->game.pos_y]
		[(int)(vars->game.pos_x - vars->game.dir_x * MOVE_SPEED)] != 1)
		{
			vars->game.pos_x -= vars->game.dir_x * MOVE_SPEED;
			vars->game.pos_y -= vars->game.dir_y * MOVE_SPEED;
			return (1);
		}
	}
	return (0);
}

/*
** Function that regulates right movement and calls the functions to move in
** all other directions. Returns whether or not move was possible, something
** changed and thus whether raycasting must be performed again.
*/

int		move(t_vars *vars)
{
	int	change;

	change = 0;
	if (front(vars))
		change = 1;
	if (left(vars))
		change = 1;
	if (back(vars))
		change = 1;
	if (vars->hooks.d == 1)
	{
		if (vars->map.array[(int)(vars->game.pos_y + vars->game.dir_x *
		MOVE_SPEED)][(int)(vars->game.pos_x - vars->game.dir_y *
		MOVE_SPEED)] != 1)
		{
			vars->game.pos_x += vars->game.plane_x * MOVE_SPEED;
			vars->game.pos_y += vars->game.plane_y * MOVE_SPEED;
			change = 1;
		}
	}
	return (change);
}
