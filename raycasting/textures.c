/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/07 10:23:12 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/09 19:44:20 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	draw_ceiling_and_floor(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < vars->game.draw_start)
	{
		my_mlx_pixel_put(&vars->image[vars->img_index], vars->game.x, i,
		vars->map.col_ceiling);
		i++;
	}
	i = vars->game.draw_end;
	while (i < vars->image[vars->img_index].img_height)
	{
		my_mlx_pixel_put(&vars->image[vars->img_index], vars->game.x, i,
		vars->map.col_floor);
		i++;
	}
}

void	draw_line(t_vars *vars, int tex_x)
{
	int				tex_num;
	int				tex_height;
	double			tex_pos;
	int				y;
	int				tex_y;

	tex_num = vars->game.wall_type;
	tex_height = vars->game.textures[tex_num].img_height;
	vars->game.step = 1 * (double)tex_height / (double)vars->game.line_height;
	tex_pos = (vars->game.draw_start - vars->image[vars->img_index].img_height
	/ 2 + vars->game.line_height / 2) * vars->game.step;
	y = vars->game.draw_start;
	while (y < vars->game.draw_end)
	{
		tex_y = (int)tex_pos & (tex_height - 1);
		tex_pos += vars->game.step;
		vars->game.color = vars->game.textures[tex_num].int_addr[tex_height *
		tex_y + tex_x];
		if (vars->game.side == Y)
			vars->game.color = add_shade(0.4, vars->game.color);
		my_mlx_pixel_put(&vars->image[vars->img_index], vars->game.x, y,
		vars->game.color);
		y++;
	}
	draw_ceiling_and_floor(vars);
}

void	textures(t_vars *vars, int draw_start, int draw_end, int line_height)
{
	int		tex_num;
	double	wall_x;
	int		tex_x;

	tex_num = vars->game.wall_type;
	if (vars->game.side == X)
		wall_x = vars->game.pos_x + vars->game.perp_wall_dist *
		vars->game.ray_dir_x;
	else
		wall_x = vars->game.pos_y + vars->game.perp_wall_dist *
		vars->game.ray_dir_y;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)vars->game.textures[tex_num].img_width);
	if (tex_num == SO || tex_num == WE)
		tex_x = (double)vars->game.textures[tex_num].img_width - tex_x - 1;
	draw_line(vars, tex_x);
}
