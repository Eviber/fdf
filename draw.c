/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 22:30:11 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/28 00:12:24 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minilibx_macos/mlx.h"

typedef struct	s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct	s_line
{
	t_point		a;
	t_point		b;
}				t_line;

typedef struct	s_mlxdata
{
	void			*mlx;
	void			*win;
	void			*imgptr;
	char			*img;
	int				bpp;
	int				sizeline;
	int				endian;
}				t_mlxdata;

void		imgputpixel(t_mlxdata dt, t_point pos, unsigned int color)
{
	unsigned int	*addr;

	addr = (unsigned int *)(dt.img + (dt.sizeline * pos.y) + (pos.x * dt.bpp));
	if (pos.x < 640 && pos.y < 480)
		*addr = color;
}

void		ft_fswap(double *a, double *b)
{
	double	c;

	c = *a;
	*a = *b;
	*b = c;
}

double		fpart(double n)
{
	return (n - floor(n));
}

double		rfpart(double n)
{
	return (1 - fpart(n));
}

void		drawline(t_mlxdata data, double x0, double y0, double x1, double y1, unsigned int color)
{
	double	gradient;
	double	dx;
	double	dy;
	double	xend;
	double	yend;
	double	xpx11;
	double	ypx11;
	double	xpx12;
	double	ypx12;
	double	intery;
	double	x;
	float	xgap;
	int		steep;

	steep = (fabs(y1 - y0) > fabs(x1 - x0));
	if (steep)
	{
		ft_fswap(&x0, &y0);
		ft_fswap(&x1, &y1);
	}
	if (x0 > x1)
	{
		ft_fswap(&x0, &x1);
		ft_fswap(&y0, &y1);
	}

	dx = x1 - x0;
	dy = y1 - y0;
	gradient = dy / dx;
	if (dx == 0.0)
		gradient = 1.0;

// handle first endpoint
	xend = floor(x0) + 0.5;
	yend = y0 + gradient * (xend - x0);
	xgap = rfpart(x0 + 0.5);
	xpx11 = xend;
	ypx11 = floor(yend);
	if (steep)
	{
		plot(ypx11, xpx11, rfpart(yend) * xgap);
		plot(ypx11 + 1, xpx11, fpart(yend) * xgap);
	}
	else
	{
		plot(xpx11, ypx11, rfpart(yend) * xgap);
		plot(xpx11, ypx11 + 1, fpart(yend) * xgap);
	}
	intery = yend + gradient;

// handle second endpoint
	xend = floor(x1) + 0.5;
	yend = y1 + gradient * (xend - x1);
	xgap = fpart(x1 + 0.5);
	xpx12 = xend;
	ypx12 = floor(yend);
	if (steep)
	{
		plot(ypx12, xpx12, rfpart(yend) * xgap);
		plot(ypx12 + 1, xpx12, fpart(yend) * xgap);
	}
	else
	{
		plot(xpx12, ypx12, rfpart(yend) * xgap);
		plot(xpx12, ypx12 + 1, fpart(yend) * xgap);
	}

// main loop
	if (steep)
	{
		for (x = xpx11 + 1 ; x < xpx12 - 1 ; x++)
		{
			plot(floor(intery), x, rfpart(intery));
			plot(floor(intery) + 1, x, fpart(intery));
			intery += gradient;
		}
	}
	else
	{
		for (x = xpx11 + 1 ; x < xpx12 - 1 ; x++)
		{
			plot(x, floor(intery), rfpart(intery));
			plot(x, floor(intery) + 1, fpart(intery));
			intery += gradient;
		}
	}
}
