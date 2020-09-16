/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_map_array.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/18 11:12:07 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/03 12:18:34 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	make_lines(t_info *map, int ***array, int count_sprites)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (i < map->ymax)
	{
		j = 0;
		while (j < map->xmax)
		{
			if (map->whole_map[k] == '2' && count_sprites == 1)
				map->num_sprites++;
			if (map->whole_map[k] == '\n')
				break ;
			else
				(*array)[i][j] = (int)map->whole_map[k] - '0';
			j++;
			k++;
		}
		i++;
		k++;
	}
}

int		make_map_array(t_info *map, int ***array, int count_sprites)
{
	int i;

	i = 0;
	(*array) = malloc(map->ymax * sizeof(int *));
	if (*array == NULL)
		return (-1);
	while (i < map->ymax)
	{
		(*array)[i] = ft_calloc(map->xmax, sizeof(int));
		if ((*array)[i] == NULL)
			return (-1);
		i++;
	}
	make_lines(map, array, count_sprites);
	return (0);
}
