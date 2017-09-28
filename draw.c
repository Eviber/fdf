/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 22:30:11 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/28 06:19:01 by ygaude           ###   ########.fr       */
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

typedef struct	s_wu
{
	double	gradient;
	t_point	end;
	t_point	pxstart;
	t_point	pxend;
	double	intery;
	int		steep;
}				t_wu;

void		imgputpixel(int x, int y, unsigned int color)
{
	t_mlxdata	dt;
	unsigned int	*addr;

	dt = getmlxdata(NULL);
	addr = (unsigned int *)(dt.img + (dt.sizeline * y) + (x * dt.bpp));
	if (x < 640 && y < 480)
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
/*
void		drawline_(t_mlxdata data, t_point a, t_point b, unsigned int color)
{
	double	gradient;
	t_point	diff;
	t_point	end;
	t_point	pxstart;
	t_point	pxend;
	double	intery;
	float	xgap;
	int		steep;

	steep = (fabs(b.y - a.y) > fabs(b.x - a.x));
	if (steep)
	{
		ft_fswap(&a.x, &a.y);
		ft_fswap(&b.x, &b.y);
	}
	if (a.x > b.x)
	{
		ft_fswap(&a.x, &b.x);
		ft_fswap(&a.y, &b.y);
	}

	d.x = b.x - a.x;
	d.y = b.y - a.y;
	gradient = d.y / d.x;
	if (d.x == 0.0)
		gradient = 1.0;

// handle first endpoint
	end.x = floor(a.x) + 0.5;
	end.y = a.y + gradient * (end.x - a.x);
	xgap = rfpart(a.x + 0.5);
	pxstart.x = end.x;
	pxstart.y = floor(end.y);
	if (steep)
	{
		plot(pxstart.y, pxstart.x, rfpart(end.y) * xgap);
		plot(pxstart.y + 1, pxstart.x, fpart(end.y) * xgap);
	}
	else
	{
		plot(pxstart.x, pxstart.y, rfpart(end.y) * xgap);
		plot(pxstart.x, pxstart.y + 1, fpart(end.y) * xgap);
	}
	intery = end.y + gradient;

// handle second endpoint
	end.x = floor(b.x) + 0.5;
	end.y = b.y + gradient * (end.x - b.x);
	xgap = fpart(b.x + 0.5);
	pxend.x = end.x;
	pxend.y = floor(end.y);
	if (steep)
	{
		plot(pxend.y, pxend.x, rfpart(end.y) * xgap);
		plot(pxend.y + 1, pxend.x, fpart(end.y) * xgap);
	}
	else
	{
		plot(pxend.x, pxend.y, rfpart(end.y) * xgap);
		plot(pxend.x, pxend.y + 1, fpart(end.y) * xgap);
	}

// main loop
	if (steep)
	{
		for (x = pxstart.x + 1 ; x < pxend.x - 1 ; x++)
		{
			plot(floor(intery), x, rfpart(intery));
			plot(floor(intery) + 1, x, fpart(intery));
			intery += gradient;
		}
	}
	else
	{
		for (x = pxstart.x + 1 ; x < pxend.x - 1 ; x++)
		{
			plot(x, floor(intery), rfpart(intery));
			plot(x, floor(intery) + 1, fpart(intery));
			intery += gradient;
		}
	}
}
*/

unsigned int	setal(float a, unsigned int rgb)
{
	return ((((char)round(a * 255)) << 24) + rgb);
}

t_wu		endpoints(t_wu wu, t_point a, t_point b, unsigned int color)
{
	t_point	end;
	float	xgap;

// handle first endpoint
	end.x = floor(a.x) + 0.5;
	end.y = a.y + wu.gradient * (end.x - a.x);
	xgap = rfpart(a.x + 0.5);
	wu.pxstart.x = end.x;
	wu.pxstart.y = floor(end.y);
	if (wu.steep)
	{
		imgputpixel(wu.pxstart.y, wu.pxstart.x, setal(rfpart(end.y) * xgap, color));
		imgputpixel(wu.pxstart.y + 1, wu.pxstart.x, setal(fpart(end.y) * xgap, color));
	}
	else
	{
		imgputpixel(wu.pxstart.x, wu.pxstart.y, setal(rfpart(end.y) * xgap, color));
		imgputpixel(wu.pxstart.x, wu.pxstart.y + 1, setal(fpart(end.y) * xgap, color));
	}
	wu.intery = end.y + wu.gradient;

// handle second endpoint
	end.x = floor(b.x) + 0.5;
	end.y = b.y + wu.gradient * (end.x - b.x);
	xgap = fpart(b.x + 0.5);
	wu.pxend.x = end.x;
	wu.pxend.y = floor(end.y);
	if (wu.steep)
	{
		imgputpixel(wu.pxend.y, wu.pxend.x, setal(rfpart(end.y) * xgap, color));
		imgputpixel(wu.pxend.y + 1, wu.pxend.x, setal(fpart(end.y) * xgap, color));
	}
	else
	{
		imgputpixel(wu.pxend.x, wu.pxend.y, setal(rfpart(end.y) * xgap, color));
		imgputpixel(wu.pxend.x, wu.pxend.y + 1, setal(fpart(end.y) * xgap, color));
	}
	return (wu);
}

void		wu_loop(t_wu wu, unsigned int color)
{
	if (wu.steep)
	{
		while (++wu.pxstart.x < wu.pxend.x - 1)
		{
			imgputpixel(floor(wu.intery), wu.pxstart.x, setal(rfpart(wu.intery), color));
			imgputpixel(floor(wu.intery) + 1, wu.pxstart.x, setal(fpart(wu.intery), color));
			wu.intery += wu.gradient;
		}
	}
	else
	{
		while (++wu.pxstart.x < wu.pxend.x - 1)
		{
			imgputpixel(wu.pxstart.x, floor(wu.intery), setal(rfpart(wu.intery), color));
			imgputpixel(wu.pxstart.x, floor(wu.intery) + 1, setal(fpart(wu.intery), color));
			wu.intery += wu.gradient;
		}
	}
}

void		drawline_(t_point a, t_point b, unsigned int color)
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
	wu = endpoints(wu, a, b, color);
	wu_loop(wu, color);
}
