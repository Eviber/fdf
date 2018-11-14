/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 22:30:11 by ygaude            #+#    #+#             */
/*   Updated: 2018/11/14 02:10:10 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#include "fdf.h"

void		imgputpixel(int x, int y, unsigned int color)
{
	t_winenv	*env;
	int			r;
	int			g;
	int			b;
	int			a;

	a = 255 - (int)((color >> 24) & 0xFF);
	r = (int)((color >> 16) & 0xFF);
	g = (int)((color >> 8) & 0xFF);
	b = (int)(color & 0xFF);
	env = getsdlenv();
	SDL_SetRenderDrawColor(env->render, r, g, b, a);
	SDL_RenderDrawPoint(env->render, x, y);
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
	err = (d.x > d.y ? d.x : -d.y) / 2;
	while (round(a.x) != round(b.x) || round(a.y) != round(b.y))
	{
		imgputpixel(a.x, a.y, color);
		e2 = err;
		err -= d.y * (e2 > -d.x);
		a.x += sens.x * (e2 > -d.x);
		err += d.x * (e2 < d.y);
		a.y += sens.y * (e2 < d.y);
	}
}
