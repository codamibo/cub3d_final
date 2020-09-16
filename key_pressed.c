/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_pressed.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 14:14:24 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/03 12:05:51 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	clean_hooks(t_hooks *hooks)
{
	hooks->w = 0;
	hooks->a = 0;
	hooks->s = 0;
	hooks->d = 0;
	hooks->l_arrow = 0;
	hooks->r_arrow = 0;
	hooks->esc = 0;
	hooks->key_change = 0;
}

int		close_win(t_vars *vars)
{
	if (vars->image[0].img)
		mlx_destroy_image(vars->mlx, vars->image[0].img);
	if (vars->image[1].img)
		mlx_destroy_image(vars->mlx, vars->image[1].img);
	if (vars->game.textures[0].img)
		mlx_destroy_image(vars->mlx, vars->game.textures[0].img);
	if (vars->game.textures[1].img)
		mlx_destroy_image(vars->mlx, vars->game.textures[1].img);
	if (vars->game.textures[2].img)
		mlx_destroy_image(vars->mlx, vars->game.textures[2].img);
	if (vars->game.textures[3].img)
		mlx_destroy_image(vars->mlx, vars->game.textures[3].img);
	if (vars->game.textures[4].img)
		mlx_destroy_image(vars->mlx, vars->game.textures[4].img);
	if (vars->win && vars->mlx)
		mlx_destroy_window(vars->mlx, vars->win);
	free_arrays(vars);
	exit(0);
	return (0);
}

int		key_released(int keycode, t_hooks *hooks)
{
	if (keycode == 13)
		hooks->w = 0;
	else if (keycode == 0)
		hooks->a = 0;
	else if (keycode == 1)
		hooks->s = 0;
	else if (keycode == 2)
		hooks->d = 0;
	else if (keycode == 123)
		hooks->l_arrow = 0;
	else if (keycode == 124)
		hooks->r_arrow = 0;
	else if (keycode == 53)
		hooks->esc = 0;
	else
		return (0);
	return (0);
}

int		key_pressed(int keycode, t_hooks *hooks)
{
	if (keycode == 13)
		hooks->w = 1;
	else if (keycode == 0)
		hooks->a = 1;
	else if (keycode == 1)
		hooks->s = 1;
	else if (keycode == 2)
		hooks->d = 1;
	else if (keycode == 123)
		hooks->l_arrow = 1;
	else if (keycode == 124)
		hooks->r_arrow = 1;
	else if (keycode == 53)
		hooks->esc = 1;
	else
		return (0);
	hooks->key_change = 1;
	return (0);
}
