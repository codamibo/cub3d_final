/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast_loop.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/09 19:31:05 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/06 12:46:55 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	step_and_side_dist(t_positions *game)
{
	if (game->ray_dir_x < 0)
	{
		game->step_x = -1;
		game->side_dist_x = ((double)game->pos_x - (double)game->map_x) *
		game->delta_dist_x;
	}
	else
	{
		game->step_x = 1;
		game->side_dist_x = ((double)game->map_x + 1.0 - (double)game->pos_x) *
		game->delta_dist_x;
	}
	if (game->ray_dir_y < 0)
	{
		game->step_y = -1;
		game->side_dist_y = (game->pos_y - (double)game->map_y) *
		game->delta_dist_y;
	}
	else
	{
		game->step_y = 1;
		game->side_dist_y = ((double)game->map_y + 1.0 - game->pos_y) *
		game->delta_dist_y;
	}
}

void	save_dist(int x, double w, t_positions *game)
{
	game->camera_x = 2 * x / w - 1;
	game->ray_dir_x = game->dir_x + game->plane_x * game->camera_x;
	game->ray_dir_y = game->dir_y + game->plane_y * game->camera_x;
	game->map_x = (int)game->pos_x;
	game->map_y = (int)game->pos_y;
	if (game->ray_dir_y == 0)
		game->delta_dist_x = 0;
	else if (game->ray_dir_x == 0)
		game->delta_dist_x = 1;
	else
		game->delta_dist_x = fabs(1 / game->ray_dir_x);
	if (game->ray_dir_x == 0)
		game->delta_dist_y = 0;
	else if (game->ray_dir_y == 0)
		game->delta_dist_y = 1;
	else
		game->delta_dist_y = fabs(1 / game->ray_dir_y);
	step_and_side_dist(game);
}

void	perp_wall_dist(t_vars *vars)
{
	if (vars->game.side == Y)
		vars->game.perp_wall_dist = (vars->game.map_x - vars->game.pos_x +
		(1 - vars->game.step_x) / 2) / vars->game.ray_dir_x;
	else
		vars->game.perp_wall_dist = (vars->game.map_y - vars->game.pos_y +
		(1 - vars->game.step_y) / 2) / vars->game.ray_dir_y;
	vars->game.z_buffer[vars->game.x] = vars->game.perp_wall_dist;
}

void	raycast(t_vars *vars)
{
	vars->img_index = (vars->img_index == 0) ? 1 : 0;
	vars->game.x = 0;
	while (vars->game.x < vars->image[vars->img_index].img_width)
	{
		save_dist(vars->game.x, vars->game.w, &vars->game);
		dda(vars);
		perp_wall_dist(vars);
		vars->game.line_height = (vars->game.h / vars->game.perp_wall_dist);
		vars->game.draw_start = vars->game.h / 2 - vars->game.line_height / 2;
		if (vars->game.draw_start < 0)
			vars->game.draw_start = 0;
		vars->game.draw_end = vars->game.h / 2 + vars->game.line_height / 2;
		if (vars->game.draw_end >= vars->game.h)
			vars->game.draw_end = vars->game.h - 1;
		textures(vars, vars->game.draw_start, vars->game.draw_end,
		vars->game.line_height);
		vars->game.x++;
	}
	sprites(vars, &vars->sp, &vars->game);
	if (vars->argc != 3)
		mlx_put_image_to_window(vars->mlx, vars->win,
		vars->image[vars->img_index].img, 0, 0);
}

int		raycast_loop(t_vars *vars)
{
	if (vars->hooks.key_change == 1)
	{
		vars->hooks.key_change = 0;
		if (vars->hooks.esc == 1)
			close_win(vars);
		else
		{
			if (rotate(vars))
				raycast(vars);
		}
	}
	return (0);
}
