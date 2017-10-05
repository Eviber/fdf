/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:02:27 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/05 18:08:39 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "minilibx_macos/mlx.h"
#include "fdf.h"

double			fpart(double n)
{
	return (n - floor(n));
}

double			rfpart(double n)
{
	return (1 - fpart(n));
}

unsigned int	setal(float a, unsigned int rgb)
{
	return ((((char)round(255 - (a * 255))) << 24) + rgb);
}

t_color			setcolors(double diff, unsigned int from, unsigned int to)
{
	t_color	d;

	d.r = (int)((to >> 16) & 0xFF) - (int)((from >> 16) & 0xFF);
	d.g = (int)((to >> 8) & 0xFF) - (int)((from >> 8) & 0xFF);
	d.b = (int)(to & 0xFF) - (int)(from & 0xFF);
	d.r = (d.r / diff);
	d.g = (d.g / diff);
	d.b = (d.b / diff);
	return (d);
}

t_color		addcolors(t_color a, double r, double g, double b)
{
	a.r += r;
	a.g += g;
	a.b += b;
	return (a);
}
