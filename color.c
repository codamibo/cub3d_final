/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 13:07:35 by iboeters      #+#    #+#                 */
/*   Updated: 2020/05/15 13:18:40 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

unsigned int	add_shade(double amount, unsigned int color)
{
	unsigned int t;
	unsigned int r;
	unsigned int g;
	unsigned int b;

	t = color & 0xFF000000;
	r = color & 0xFF0000;
	g = color & 0xFF00;
	b = color & 0xFF;
	r = (r >> 16) * (1 - amount);
	g = (g >> 8) * (1 - amount);
	b = b * (1 - amount);
	r = r << 16;
	g = g << 8;
	return (t | r | g | b);
}

unsigned int	create_trgb(unsigned int t, unsigned int r, unsigned int g,
unsigned int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
