/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/30 14:42:54 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:33:22 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	skip_spaces(char *buf, int *i, int len)
{
	while (buf[*i] == ' ' && *i < len)
		(*i)++;
}

void	skip_characters(char *buf, int *i, int len)
{
	while (buf[*i] != ' ' && *i < len)
		(*i)++;
}

void	skip_digits(char *buf, int *i, int len)
{
	while (ft_isdigit(buf[*i]) && *i < len)
		(*i)++;
}

int		is_map_character(char c)
{
	if (c == '0' || c == '1' || c == '2' || c == 'N' || c == 'E' || c == 'S' ||
	c == 'W')
		return (1);
	return (0);
}

int		is_start_character(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}
