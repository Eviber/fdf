/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 22:30:11 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/28 16:37:47 by ygaude           ###   ########.fr       */
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
	if (x < WIN_W && y < WIN_H)
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

void		wu_loop(t_wu wu, unsigned int color)
{
	if (wu.steep)
	{
		while (++wu.pxstart.x < wu.pxend.x - 1)
		{
			imgputpixel(floor(wu.intery), wu.pxstart.x,
						setal(rfpart(wu.intery), color));
			imgputpixel(floor(wu.intery) + 1, wu.pxstart.x,
						setal(fpart(wu.intery), color));
			wu.intery += wu.gradient;
		}
	}
	else
	{
		while (++wu.pxstart.x < wu.pxend.x - 1)
		{
			imgputpixel(wu.pxstart.x, floor(wu.intery),
						setal(rfpart(wu.intery), color));
			imgputpixel(wu.pxstart.x, floor(wu.intery) + 1,
						setal(fpart(wu.intery), color));
			wu.intery += wu.gradient;
		}
	}
}

void		drawline(t_point a, t_point b, unsigned int color)
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
	}
	wu.gradient = (b.x - a.x == 0.0) ? 1.0 : (b.y - a.y) / (b.x - a.x);
	wu = endpoint1(wu, a, color);
	wu = endpoint2(wu, b, color);
	wu_loop(wu, color);
}
