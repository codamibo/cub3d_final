/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 13:39:00 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/06 14:39:35 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void		swap(int **sprite_order, double **sprite_distance, int j)
{
	int		temp_order;
	double	temp_dist;

	temp_dist = (*sprite_distance)[j];
	temp_order = (*sprite_order)[j];
	(*sprite_distance)[j] = (*sprite_distance)[j + 1];
	(*sprite_distance)[j + 1] = temp_dist;
	(*sprite_order)[j] = (*sprite_order)[j + 1];
	(*sprite_order)[j + 1] = temp_order;
}

void		bubble_sort(int **sprite_order, double **sprite_distance,
			int num_sprites)
{
	int		swapped;
	int		i;
	int		j;

	swapped = 1;
	i = 0;
	j = 0;
	while (num_sprites - i > 1 && swapped == 1)
	{
		swapped = 0;
		j = 0;
		while (j < num_sprites - i - 1)
		{
			if ((*sprite_distance)[j] < (*sprite_distance)[j + 1])
			{
				swap(sprite_order, sprite_distance, j);
				swapped = 1;
			}
			j++;
		}
		i++;
	}
}

void		sp_data(t_vars *vars, t_sprite_info *sp, t_positions *game, int i)
{
	sp->sprite_x = game->sprite[game->sprite_order[i]].x - game->pos_x;
	sp->sprite_y = game->sprite[game->sprite_order[i]].y - game->pos_y;
	sp->inverse = 1 / (game->plane_x * game->dir_y - game->plane_y *
	game->dir_x);
	sp->transform_x = sp->inverse * (game->dir_y * sp->sprite_x - game->dir_x *
	sp->sprite_y);
	sp->transform_y = sp->inverse * (-game->plane_y * sp->sprite_x +
	game->plane_x * sp->sprite_y);
	sp->sprite_screen_x = (int)((vars->image[vars->img_index].img_width / 2) *
	(1 + sp->transform_x / sp->transform_y));
	sp->width = fabs(vars->image[vars->img_index].img_height / sp->transform_y);
	sp->hei = fabs(vars->image[vars->img_index].img_height / sp->transform_y);
	sp->draw_start_x = -sp->width / 2 + sp->sprite_screen_x;
	sp->draw_start_x = (sp->draw_start_x < 0) ? 0 : sp->draw_start_x;
	sp->draw_end_x = sp->width / 2 + sp->sprite_screen_x;
	sp->draw_end_x = (sp->draw_end_x >= vars->image[vars->img_index].img_width)
	? vars->image[vars->img_index].img_width - 1 : sp->draw_end_x;
	sp->draw_start_y = -sp->hei / 2 + vars->image[vars->img_index].img_height /
	2;
	sp->draw_start_y = (sp->draw_start_y < 0) ? 0 : sp->draw_start_y;
	sp->draw_end_y = sp->hei / 2 + vars->image[vars->img_index].img_height / 2;
	sp->draw_end_y = (sp->draw_end_y >= vars->image[vars->img_index].img_height)
	? vars->image[vars->img_index].img_height - 1 : sp->draw_end_y;
}

void		draw_sp(t_vars *vars, t_sprite_info *sp, t_positions *game, int i)
{
	sp->tex_x = (int)(256 * (sp->draw_start_x - (-sp->width /
	2 + sp->sprite_screen_x)) * game->textures[S].img_width /
	sp->width) / 256;
	if (sp->transform_y > 0 && sp->draw_start_x > 0 && sp->draw_start_x
	< vars->image[vars->img_index].img_width
	&& sp->transform_y < game->z_buffer[sp->draw_start_x])
	{
		sp->y = sp->draw_start_y;
		while (sp->y < sp->draw_end_y)
		{
			sp->d = sp->y * 256 - vars->image[vars->img_index].
			img_height * 128 + sp->hei * 128;
			sp->tex_y = ((sp->d * game->textures[S].img_height) /
			sp->hei / 256);
			sp->color = game->textures[S].int_addr[game->textures[S].
			img_height * sp->tex_y + sp->tex_x];
			if (sp->color != 0x000000)
			{
				my_mlx_pixel_put(&vars->image[vars->img_index],
				sp->draw_start_x, sp->y, sp->color);
			}
			sp->y++;
		}
	}
	sp->draw_start_x++;
}

int			sprites(t_vars *vars, t_sprite_info *sp, t_positions *game)
{
	int				i;

	i = 0;
	while (i < vars->map.num_sprites)
	{
		game->sprite_order[i] = i;
		game->sprite_distance[i] = ((game->pos_x - game->sprite[i].x) *
		(game->pos_x - game->sprite[i].x) +
		(game->pos_y - game->sprite[i].y) *
		(game->pos_y - game->sprite[i].y));
		i++;
	}
	bubble_sort(&(game->sprite_order), &(game->sprite_distance),
	vars->map.num_sprites);
	i = 0;
	while (i < vars->map.num_sprites)
	{
		sp_data(vars, &vars->sp, &vars->game, i);
		while (sp->draw_start_x < sp->draw_end_x)
			draw_sp(vars, &vars->sp, &vars->game, i);
		i++;
	}
	return (0);
}
