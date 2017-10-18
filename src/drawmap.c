/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 18:43:36 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/18 20:44:44 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void		drawline(t_env env, t_intpoint i, int nextx, int nexty)
{
	t_point			px;
	unsigned int	c1;

	px = env.map.grid[i.y][i.x];
	c1 = (env.colorstyle != NONE) ? 0xFFFFFF : (env.map.array[i.y][i.x]).color;
	if (env.drawstyle != POINT)
	{
		if (env.drawstyle == WU)
			wuline(px, env.map.grid[nexty][nextx], c1, (env.colorstyle != NONE)
							? 0x00FFFFFF : (env.map.array[nexty][nextx]).color);
		if (env.drawstyle == QUICK)
			rawline(px, env.map.grid[nexty][nextx], 0x00FFFFFF);
	}
	if (env.drawstyle == POINT || env.drawstyle == QUICK)
		imgputpixel(px.x, px.y, c1);
}

void		draw_map(t_env env)
{
	t_intpoint		i;

	i.y = 0;
	while (i.y < env.map.height)
	{
		i.x = 0;
		while (i.x < env.map.width)
		{
			if (!i.x && !i.y)
				drawline(env, i, i.x, i.y);
			if (i.x)
				drawline(env, i, i.x - 1, i.y);
			if (i.y)
				drawline(env, i, i.x, i.y - 1);
			if (env.trnsvrsl && i.x && i.y)
				drawline(env, i, i.x - 1, i.y - 1);
			i.x++;
		}
		i.y++;
	}
}
