/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/30 15:07:19 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:15:40 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void		save_characters(char **str, char *buf, int *i, t_info *map)
{
	while ((*i) < map->len1 + map->len2 &&
	(is_map_character(buf[(*i) - map->len1]) || buf[(*i) - map->len1] == ' '))
	{
		if (is_start_character(buf[(*i) - map->len1]))
		{
			if (map->start_char_found == 0)
				map->start_char_found = 1;
			else
				map->multiple_start_char = 1;
			map->start_char = buf[(*i) - map->len1];
			map->xstart = (*i) - map->len1 + 0.5;
			map->ystart = map->ymax + 0.5;
			(*str)[(*i)] = '0';
		}
		else if (buf[(*i) - map->len1] == ' ')
			(*str)[(*i)] = '0';
		else
			(*str)[(*i)] = buf[(*i) - map->len1];
		(*i)++;
	}
}

void		transform_line(char **str, char *buf, int *i, t_info *map)
{
	while ((*i) < map->len1)
	{
		(*str)[(*i)] = map->whole_map[(*i)];
		(*i)++;
	}
	save_characters(str, buf, i, map);
	(*str)[(*i)] = '\n';
	(*i)++;
	(*str)[(*i)] = '\0';
	if (map->whole_map)
	{
		free((void *)map->whole_map);
		map->whole_map = NULL;
	}
}

char		*strjoin_cub(char *buf, t_info *map)
{
	char	*str;
	int		i;

	i = 0;
	map->len1 = ft_strlen(map->whole_map);
	map->len2 = ft_strlen(buf);
	str = (char*)malloc(sizeof(char) * (map->len1 + map->len2 + 2));
	if (!str)
		return (0);
	transform_line(&str, buf, &i, map);
	if (map->len2 > map->xmax)
		map->xmax = map->len2;
	if (i != map->len1 + map->len2 + 1)
	{
		if (map->whole_map)
			free(map->whole_map);
		return (0);
	}
	return (str);
}

int			save_map(char *buf, t_vars *vars)
{
	if (all_elem_found(&(vars->map)))
		parse_return(vars, "Error:\nElement(s) missing before map\n", 1);
	if (ft_strlen(buf) == 0)
		vars->map.empty_line = 1;
	else if (ft_strlen(buf) > 0 && vars->map.empty_line == 1)
		parse_return(vars, "Error:\nNewline in map\n", 1);
	vars->map.whole_map = strjoin_cub(buf, &vars->map);
	if (vars->map.whole_map == 0)
		return (-1);
	vars->map.ymax++;
	return (0);
}
