/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 18:43:36 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/16 20:18:00 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "minilibx_macos/mlx.h"
#include "libft.h"
#include "fdf.h"

void		draw_grid(t_env env)
{
	t_point	pt;
	t_point	px;
	t_point	px2;

	pt.x = 0;
	pt.y = 0;
	if (env.rot > env.d.x || env.rot < -env.d.x)
		env.d.y = (env.rot > env.d.x) ? env.rot - 2 * (env.rot - env.d.x) :
										env.rot - 2 * (env.rot + env.d.x);
	while (pt.y < env.map.height)
	{
		px.x = pt.x * env.d.x + (pt.y * env.d.x);
		px.y = env.start - (pt.x * env.d.y) + (pt.y * env.d.y);
		px2.x = (env.map.width - 1) * env.d.x + (pt.y * env.d.x);
		px2.y = env.start - ((env.map.width - 1) * env.d.y) + (pt.y * env.d.y);
		rawline(px, px2, 0xCCFFFFFF);
		pt.y++;
	}
	pt.y = 0;
	while (pt.x < env.map.width)
	{
		px.x = pt.x * env.d.x + (pt.y * env.d.x);
		px.y = env.start - (pt.x * env.d.y) + (pt.y * env.d.y);
		px2.x = pt.x * env.d.x + ((env.map.height - 1) * env.d.x);
		px2.y = env.start - (pt.x * env.d.y) + ((env.map.height - 1) * env.d.y);
		rawline(px, px2, 0xCCFFFFFF);
		pt.x++;
	}
}

void		calc_map(t_env env)
{
	t_fdfval	**array;
	t_point		px;
	int			x;
	int			y;

	y = -1;
	array = env.map.array;
	while (++(y) < env.map.height && (x = -1))
	{
		while (++(x) < env.map.width)
		{
			px.x = x * env.d.x + (y * env.d.x);
			px.y = env.start - (x * env.d.y) + (y * env.d.y) +
					(array[(int)y][(int)x]).alti * env.dh;
			env.map.grid[y][x] = px;
		}
	}
}

void		draw_map_wu(t_env env)
{
	t_intpoint		i;
	t_point			px;
	t_point			px2;
	unsigned int	c1;
	unsigned int	c2;

	i.y = 0;
	c1 = 0x00FFFFFF;
	c2 = 0x00FFFFFF;
	while (i.y < env.map.height)
	{
		i.x = 0;
		while (i.x < env.map.width)
		{
			px = env.map.grid[i.y][i.x];
			if (env.colorstyle != NONE)
				c1 = (env.map.array[i.y][i.x]).color;
			if (i.x)
			{
				if (env.colorstyle != NONE)
					c2 = (env.map.array[i.y][i.x - 1]).color;
				px2 = env.map.grid[i.y][i.x - 1];
				drawline(px, px2, c1, c2);
			}
			if (i.y)
			{
				if (env.colorstyle != NONE)
					c2 = (env.map.array[i.y - 1][i.x]).color;
				px2 = env.map.grid[i.y - 1][i.x];
				drawline(px, px2, c1, c2);
			}
			if (env.trnsvrsl && i.x && i.y)
			{
				if (env.colorstyle != NONE)
					c2 = (env.map.array[i.y - 1][i.x - 1]).color;
				px2 = env.map.grid[i.y - 1][i.x - 1];
				drawline(px, px2, c1, c2);
			}
			i.x++;
		}
		i.y++;
	}
}

void		draw_map_quick(t_env env)
{
	t_intpoint		i;
	t_point			px;
	t_point			px2;
	unsigned int	c1;
	unsigned int	c2;

	i.y = 0;
	c1 = 0x00FFFFFF;
	c2 = 0x00FFFFFF;
	while (i.y < env.map.height)
	{
		i.x = 0;
		while (i.x < env.map.width)
		{
			px = env.map.grid[i.y][i.x];
			if (env.colorstyle != NONE)
				c1 = (env.map.array[i.y][i.x]).color;
			if (i.x)
			{
				if (env.colorstyle != NONE)
					c2 = (env.map.array[i.y][i.x - 1]).color;
				px2 = env.map.grid[i.y][i.x - 1];
				drawline(px, px2, c1, c2);
			}
			if (i.y)
			{
				if (env.colorstyle != NONE)
					c2 = (env.map.array[i.y - 1][i.x]).color;
				px2 = env.map.grid[i.y - 1][i.x];
				drawline(px, px2, c1, c2);
			}
			if (env.trnsvrsl && i.x && i.y)
			{
				if (env.colorstyle != NONE)
					c2 = (env.map.array[i.y - 1][i.x - 1]).color;
				px2 = env.map.grid[i.y - 1][i.x - 1];
				drawline(px, px2, c1, c2);
			}
			i.x++;
		}
		i.y++;
	}
}

void		draw_map_pt(t_env env)
{
	int				x;
	int				y;
	t_point			px;
	unsigned int	color;

	y = 0;
	color = 0x00FFFFFF;
	while (y < env.map.height)
	{
		x = 0;
		while (x < env.map.width)
		{
			px = env.map.grid[y][x];
			if (env.colorstyle != NONE)
				color = (env.map.array[y][x]).color;
			imgputpixel(px.x, px.y, color);
			x++;
		}
		y++;
	}
}
