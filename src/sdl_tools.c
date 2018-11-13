/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:31:53 by ygaude            #+#    #+#             */
/*   Updated: 2018/11/13 21:59:42 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "fdf.h"

SDL_Texture			*strtotex(char *str, t_winenv env, TTF_Font *f)
{
	SDL_Texture		*tex;
	SDL_Surface		*surf;
	SDL_Color		color;

	color = (SDL_Color){255, 255, 255, 255};
	surf = TTF_RenderText_Blended(f, str, color);
	if (!surf)
		panic("Failed creating text surface", SDL_GetError());
	tex = SDL_CreateTextureFromSurface(env.render, surf);
	if (!tex)
		panic("Failed converting surface to texture", SDL_GetError());
	SDL_FreeSurface(surf);
	return (tex);
}

double				dist(double x1, double y1, double x2, double y2)
{
	double		dx;
	double		dy;

	dx = x1 - x2;
	dy = y1 - y2;
	return (fabs(sqrt(dx * dx + dy * dy)));
}

void				panic(const char *str, const char *str2)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str2, 2);
	exit(-1);
}

t_winenv			*getsdlenv(void)
{
	static t_winenv	*winenv = NULL;

	if (!winenv)
		winenv = (t_winenv *)ft_memalloc(sizeof(t_winenv));
	return (winenv);
}

int					quitvisu(t_winenv *env)
{
	if (!env || env->quit)
	{
		TTF_CloseFont(env->bigfont);
		TTF_CloseFont(env->font);
		SDL_DestroyTexture(env->tex);
		SDL_DestroyRenderer(env->render);
		SDL_DestroyWindow(env->win);
		ft_memdel((void **)&env);
		SDL_Quit();
		return (0);
	}
	return (1);
}
