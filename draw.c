/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 22:30:11 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/05 15:22:51 by ygaude           ###   ########.fr       */
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
		imgputpixel(wu.pxend.y, wu.pxend.x,
					setal(rfpart(end.y) * xgap, color));
		imgputpixel(wu.pxend.y + 1, wu.pxend.x,
					setal(fpart(end.y) * xgap, color));
	}
	else
	{
		imgputpixel(wu.pxend.x, wu.pxend.y,
					setal(rfpart(end.y) * xgap, color));
		imgputpixel(wu.pxend.x, wu.pxend.y + 1,
					setal(fpart(end.y) * xgap, color));
	}
	return (wu);
}

void		wu_loop(t_wu wu, unsigned int fromcolor, unsigned int tocolor)
{
	t_color	cur;
	t_color	d;

	ft_memset(&cur, 0, sizeof(t_color));
	d = setcolors(wu, fromcolor, tocolor);
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

void		bresenheim()
{
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

/////////////////////////////////////////////////////////////////////////////////////////////////
#define DH -1

void	draw_grid(t_map map)
{
	t_point	pt;
	t_point	px;
	t_point	px2;
	t_point	D;
	int		startpoint;

	D.x = WIN_W / (map.width + map.height);
	D.y = D.x / 2;
	startpoint = D.y * (map.width + 1);
	pt.x = 0;
	pt.y = 0;
	while (pt.y < map.height)
	{
		px.x = pt.x * D.x + (pt.y * D.x);
		px.y = startpoint - (pt.x * D.y) + (pt.y * D.y);
		px2.x = (map.width - 1) * D.x + (pt.y * D.x);
		px2.y = startpoint - ((map.width - 1) * D.y) + (pt.y * D.y);
		drawline(px, px2, 0xEEFFFFFF, 0xEEFFFFFF);
		pt.y++;
	}
	pt.y = 0;
	while (pt.x < map.width)
	{
		px.x = pt.x * D.x + (pt.y * D.x);
		px.y = startpoint - (pt.x * D.y) + (pt.y * D.y);
		px2.x = pt.x * D.x + ((map.height - 1) * D.x);
		px2.y = startpoint - (pt.x * D.y) + ((map.height - 1) * D.y);
		drawline(px, px2, 0xEEFFFFFF, 0xEEFFFFFF);
		pt.x++;
	}
}

void	draw_map(t_map map)
{
	t_point	pt;
	t_point	px;
	t_point	px2;
	t_point	D;
	int		startpoint;

	D.x = WIN_W / (map.width + map.height);
	D.y = D.x / 2;
	pt.y = 0;
	startpoint = D.y * (map.width + 1);
	while (pt.y < map.height)
	{
		pt.x = 0;
		while (pt.x < map.width)
		{
			px.x = pt.x * D.x + (pt.y * D.x);
			px.y = startpoint - (pt.x * D.y) + (pt.y * D.y) + map.array[(int)pt.y][(int)pt.x] * DH;
			if (pt.x)
			{
				px2.x = (pt.x - 1) * D.x + (pt.y * D.x);
				px2.y = startpoint - ((pt.x - 1) * D.y) + (pt.y * D.y) + map.array[(int)pt.y][(int)pt.x - 1] * DH;
				drawline(px, px2, 0x00FFFFFF, 0x00FFFFFF);
			}
			if (pt.y)
			{
				px2.x = pt.x * D.x + ((pt.y - 1) * D.x);
				px2.y = startpoint - (pt.x * D.y) + ((pt.y - 1) * D.y) + map.array[(int)pt.y - 1][(int)pt.x] * DH;
				drawline(px, px2, 0x00FFFFFF, 0x00FFFFFF);
			}
			if (pt.x && pt.y)
			{
				px2.x = (pt.x - 1) * D.x + ((pt.y - 1) * D.x);
				px2.y = startpoint - ((pt.x - 1) * D.y) + ((pt.y - 1) * D.y) + map.array[(int)pt.y - 1][(int)pt.x - 1] * DH;
				drawline(px, px2, 0x00FFFFFF, 0x00FFFFFF);
			}
			pt.x++;
		}
		pt.y++;
	}
}
