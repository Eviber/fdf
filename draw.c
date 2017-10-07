/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 22:30:11 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/07 11:41:21 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "minilibx_macos/mlx.h"
#include "libft.h"
#include "fdf.h"

void		imgputpixel(int x, int y, unsigned int color)
{
	t_mlxdata		*dt;
	unsigned int	*addr;

	dt = getmlxdata(NULL);
	addr = (unsigned int *)(dt->img + (dt->sizeline * y) + (x * dt->bpp));
	if (0 <= x && x < WIN_W && 0 <= y &&  y < WIN_H)
		*addr = color;
}

t_wu		endpoint1(t_wu wu, t_point a, unsigned int color)
{
	t_point	end;
	float	xgap; 
	end.x = floor(a.x) + 0.5;
	end.y = a.y + wu.gradient * (end.x - a.x);
	xgap = rfpart(a.x + 0.5);
	wu.pxstart.x = end.x;
	wu.pxstart.y = floor(end.y);
	if (wu.steep)
	{
		imgputpixel(wu.pxstart.y, wu.pxstart.x,
					setal(rfpart(end.y) * xgap, color));
		imgputpixel(wu.pxstart.y + 1, wu.pxstart.x,
					setal(fpart(end.y) * xgap, color));
	}
	else
	{
		imgputpixel(wu.pxstart.x, wu.pxstart.y,
					setal(rfpart(end.y) * xgap, color));
		imgputpixel(wu.pxstart.x, wu.pxstart.y + 1,
					setal(fpart(end.y) * xgap, color));
	}
	wu.intery = end.y + wu.gradient;
	return (wu);
}

t_wu		endpoint2(t_wu wu, t_point b, unsigned int color)
{
	t_point	end;
	float	xgap;

	end.x = floor(b.x) + 0.5;
	end.y = b.y + wu.gradient * (end.x - b.x);
	xgap = fpart(b.x + 0.5);
	wu.pxend.x = end.x;
	wu.pxend.y = floor(end.y);
	if (wu.steep)
	{
		imgputpixel(wu.pxend.y, wu.pxend.x, setal(rfpart(end.y) * xgap, color));
		imgputpixel(wu.pxend.y + 1, wu.pxend.x, setal(fpart(end.y) * xgap,
																		color));
	}
	else
	{
		imgputpixel(wu.pxend.x, wu.pxend.y, setal(rfpart(end.y) * xgap, color));
		imgputpixel(wu.pxend.x, wu.pxend.y + 1, setal(fpart(end.y) * xgap,
																		color));
	}
	return (wu);
}

void		wu_loop(t_wu wu, unsigned int fromcolor, unsigned int tocolor)
{
	t_color	cur;
	t_color	d;

	ft_memset(&cur, 0, sizeof(t_color));
	d = setcolors(wu.pxend.x - wu.pxstart.x, fromcolor, tocolor);
	while (++wu.pxstart.x < wu.pxend.x)
	{
		if (wu.steep)
			imgputpixel(floor(wu.intery), wu.pxstart.x,
						setal(rfpart(wu.intery), fromcolor));
		if (wu.steep)
			imgputpixel(floor(wu.intery) + 1, wu.pxstart.x,
						setal(fpart(wu.intery), fromcolor));
		if (!wu.steep)
			imgputpixel(wu.pxstart.x, floor(wu.intery),
						setal(rfpart(wu.intery), fromcolor));
		if (!wu.steep)
			imgputpixel(wu.pxstart.x, floor(wu.intery) + 1,
						setal(fpart(wu.intery), fromcolor));
		wu.intery += wu.gradient;
		cur = addcolors(cur, d.r, d.g, d.b);
		fromcolor += ((int)round(cur.r) << 16) + ((int)round(cur.g) << 8) +
						round(cur.b);
		cur = addcolors(cur, -round(cur.r), -round(cur.g), -round(cur.b));
	}
}

void		ft_uiswap(unsigned int *a, unsigned int *b)
{
	unsigned int	c;

	c = *a;
	*a = *b;
	*b = c;
}

void		rawline(t_point a, t_point b, unsigned int color)
{
	t_point	d;
	t_point	sens;
	double	err;
	double	e2;

	d.x = round(fabs(b.x - a.x));
	d.y = round(fabs(b.y - a.y));
	sens.x = a.x < b.x ? 1 : -1;
	sens.y = a.y < b.y ? 1 : -1;
	err = (d.x > d.y ? d.x : - d.y) / 2;
	while(round(a.x) != round(b.x) || round(a.y) != round(b.y))
	{
		imgputpixel(a.x, a.y, color);
		e2 = err;
		err -= d.y * (e2 > -d.x);
		a.x += sens.x * (e2 > -d.x);
		err += d.x * (e2 < d.y);
		a.y += sens.y * (e2 < d.y);
	}
}

void		drawline(t_point a, t_point b, unsigned int scol, unsigned int ecol)
{
	t_wu	wu;

	wu.steep = (fabs(b.y - a.y) > fabs(b.x - a.x));
	if (wu.steep)
	{
		ft_fswap(&a.x, &a.y);
		ft_fswap(&b.x, &b.y);
	}
	if (a.x > b.x)
	{
		ft_fswap(&a.x, &b.x);
		ft_fswap(&a.y, &b.y);
		ft_uiswap(&scol, &ecol);
	}
	wu.gradient = (b.x - a.x == 0.0) ? 1.0 : (b.y - a.y) / (b.x - a.x);
	wu = endpoint1(wu, a, scol);
	wu = endpoint2(wu, b, ecol);
	wu_loop(wu, scol, ecol);
}

void	draw_grid(t_env env)
{
	t_point	pt;
	t_point	px;
	t_point	px2;

	pt.x = 0;
	pt.y = 0;
	if (env.rot> env.d.x || env.rot < -env.d.x)
		env.d.y = (env.rot > env.d.x) ? env.rot - 2 * (env.rot - env.d.x) :
										env.rot - 2 * (env.rot + env.d.x);
	while (pt.y < env.map.height)
	{
		px.x = pt.x * env.d.x + (pt.y * env.d.x);
		px.y = env.startpoint - (pt.x * env.d.y) + (pt.y * env.d.y);
		px2.x = (env.map.width - 1) * env.d.x + (pt.y * env.d.x);
		px2.y = env.startpoint - ((env.map.width - 1) * env.d.y) + (pt.y * env.d.y);
		rawline(px, px2, 0xCCFFFFFF);
		pt.y++;
	}
	pt.y = 0;
	while (pt.x < env.map.width)
	{
		px.x = pt.x * env.d.x + (pt.y * env.d.x);
		px.y = env.startpoint - (pt.x * env.d.y) + (pt.y * env.d.y);
		px2.x = pt.x * env.d.x + ((env.map.height - 1) * env.d.x);
		px2.y = env.startpoint - (pt.x * env.d.y) + ((env.map.height - 1) * env.d.y);
		rawline(px, px2, 0xCCFFFFFF);
		pt.x++;
	}
}

void	draw_map(t_env env)
{
	t_point	pt;
	t_point	px;
	t_point	px2;

	pt.y = 0;
	printf("env.d.rot = %f ; env.d.y = %f\n", env.rot, env.d.y);
	while (pt.y < env.map.height)
	{
		pt.x = 0;
		while (pt.x < env.map.width)
		{
			px.x = pt.x * env.d.x + (pt.y * env.d.x);
			px.y = env.startpoint - (pt.x * env.d.y) + (pt.y * env.d.y) + env.map.array[(int)pt.y][(int)pt.x] * env.dh;
			if (pt.x)
			{
				px2.x = (pt.x - 1) * env.d.x + (pt.y * env.d.x);
				px2.y = env.startpoint - ((pt.x - 1) * env.d.y) + (pt.y * env.d.y) + env.map.array[(int)pt.y][(int)pt.x - 1] * env.dh;
				drawline(px, px2, 0x00FFFFFF, 0x00FFFFFF);
			}
			if (pt.y)
			{
				px2.x = pt.x * env.d.x + ((pt.y - 1) * env.d.x);
				px2.y = env.startpoint - (pt.x * env.d.y) + ((pt.y - 1) * env.d.y) + env.map.array[(int)pt.y - 1][(int)pt.x] * env.dh;
				drawline(px, px2, 0x00FFFFFF, 0x00FFFFFF);
			}
			if (0 && pt.x && pt.y)
			{
				px2.x = (pt.x - 1) * env.d.x + ((pt.y - 1) * env.d.x);
				px2.y = env.startpoint - ((pt.x - 1) * env.d.y) + ((pt.y - 1) * env.d.y) + env.map.array[(int)pt.y - 1][(int)pt.x - 1] * env.dh;
				drawline(px, px2, 0x00FFFFFF, 0x00FFFFFF);
			}
			pt.x++;
		}
		pt.y++;
	}
}
