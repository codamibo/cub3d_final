/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/18 18:55:53 by iboeters      #+#    #+#                 */
/*   Updated: 2020/05/21 09:30:35 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void		save_sprites(t_vars *vars, t_sprite **sprite, int **sprite_order,
			double **sprite_distance)
{
	int x;
	int y;
	int num;

	x = 0;
	y = 0;
	num = 0;
	(*sprite) = malloc(vars->map.num_sprites * sizeof(t_sprite));
	(*sprite_order) = malloc(vars->map.num_sprites * sizeof(int));
	(*sprite_distance) = malloc(vars->map.num_sprites * sizeof(double));
	while (y < vars->map.ymax)
	{
		x = 0;
		while (x < vars->map.xmax)
		{
			if (vars->map.array[y][x] == 2)
			{
				vars->game.sprite[num].x = (double)x + 0.5;
				vars->game.sprite[num].y = (double)y + 0.5;
				num++;
			}
			x++;
		}
		y++;
	}
}
