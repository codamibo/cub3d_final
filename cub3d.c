/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/12 09:51:25 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:39:31 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*
** Mlx_pixel_put is very slow:
** push pixel instantly without waiting for rendering whole image
** if statement so that pixels never written outside picture boundaries
** mlx_get_data_addr() returns one big character pointer to all pixels of
** the image: 4 * as big as (width * heigth) of the image:
** R | G | B | alpha for all pixels. To get to right pixel to change its color:
** dst = addr + (y * line_length + x * (bpp / 8))
*/

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char *dst;

	if (x <= img->img_width && x >= 0 && y >= 0 && y <= img->img_height)
	{
		dst = img->addr +
		(y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

/*
** Function outputs error and exits mlx
*/

int		return_error(char *error)
{
	ft_putstr_fd(error, 1);
	exit(0);
	return (-1);
}

/*
** Function intiates the window, and two images, including addresess: one
** image to display and the other one to alter in the back.
*/

int		mlx_setup(t_vars *vars, int argc)
{
	vars->img_index = 1;
	if (argc != 3)
	{
		vars->win = mlx_new_window(vars->mlx, vars->image[0].img_width,
		vars->image[0].img_height, "cube3D");
		if (vars->win == NULL)
			return (return_error("Error:\nFailed to create new window\n"));
		mlx_clear_window(vars->mlx, vars->win);
	}
	vars->image[0].img = mlx_new_image(vars->mlx, vars->image[0].img_width,
	vars->image[0].img_height);
	if (vars->image[0].img == NULL)
		return (return_error("Error:\nFailed to create new image\n"));
	vars->image[0].addr = mlx_get_data_addr(vars->image[0].img,
	&vars->image[0].bits_per_pixel, &vars->image[0].line_length,
	&vars->image[0].endian);
	vars->image[1].img = mlx_new_image(vars->mlx, vars->image[1].img_width,
	vars->image[1].img_height);
	if (vars->image[1].img == NULL)
		return (return_error("Error:\nFailed to create new image\n"));
	vars->image[1].addr = mlx_get_data_addr(vars->image[1].img,
	&vars->image[1].bits_per_pixel, &vars->image[1].line_length,
	&vars->image[1].endian);
	return (0);
}

/*
** Error function for wrong number of arguments or if a second argument
** that is not --save
*/

int		argument_error(int argc)
{
	if (argc < 2)
		ft_putstr_fd("Error:\nMap is not specified\n", 1);
	else if (argc > 3)
		ft_putstr_fd("Error:\nToo many arguments for function to call\n", 1);
	else
		ft_putstr_fd("Error:\nSecond argument must be --save\n", 1);
	return (-1);
}

/*
** Main loop which has mlx_init(), the raycasting, all mlx_hooks
** and close_win in it. Close win destroys images, frees arrays
** and exists from the mlx_loop.
** 17 should be used as X11 event: 17 == DestroyNotify
** to close properly when red cross is pressed; with 0 as mask.
*/

int		main(int argc, char **argv)
{
	t_vars			vars;

	if (argc > 3 || argc < 2 || (argc == 3 && (ft_strlen(argv[2]) != 6 ||
	ft_strncmp(argv[2], "--save", 6))))
		return (argument_error(argc));
	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		return (return_error("Error:\nFailed to connect to display\n"));
	parse(argv, &vars, argc);
	if (mlx_setup(&vars, argc) == -1)
		return (-1);
	clean_hooks(&vars.hooks);
	save_sprites(&vars, &(vars.game.sprite), &(vars.game.sprite_order),
	&(vars.game.sprite_distance));
	raycast_setup(&vars);
	if (argc == 3)
		return (screenshot(&vars));
	mlx_loop_hook(vars.mlx, raycast_loop, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_pressed, &(vars.hooks));
	mlx_hook(vars.win, 3, 1L << 1, key_released, &(vars.hooks));
	mlx_hook(vars.win, 17, 0, close_win, &vars);
	mlx_loop(vars.mlx);
	close_win(&vars);
	return (0);
}
