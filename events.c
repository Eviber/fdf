/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 21:32:04 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/16 20:05:27 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "minilibx_macos/mlx.h"
#include "libft.h"
#include "fdf.h"

void	update(t_env env)
{
	t_mlxdata	*mlxdata;

	mlxdata = getmlxdata(NULL);
	ft_memset(mlxdata->img, 0, mlxdata->sizeline * WIN_H);
	mlx_put_image_to_window(mlxdata->mlx, mlxdata->win, mlxdata->imgptr, 0, 0);
	draw(env);
	mlx_put_image_to_window(mlxdata->mlx, mlxdata->win, mlxdata->imgptr, 0, 0);
}

void	rotate(t_env *env, int key)
{
	env->rot += 5 * (env->d.x / 100) * ((key == ARROW_UP) ? -1 : 1);
	if (env->rot > env->d.x * 2 || env->rot < -env->d.x * 2)
		env->rot = (env->rot > 0) ? -env->d.x * 2 : env->d.x * 2;
	env->dh = env->dhmax * (fabs(env->rot) - env->d.x) / env->d.x;
	env->d.y = env->rot;
	if (env->rot < -env->d.x)
		env->d.y = env->rot - 2 * (env->rot + env->d.x);
	else if (env->rot > env->d.x)
		env->d.y = env->rot - 2 * (env->rot - env->d.x);
	env->start = WIN_H / 2 - ((env->map.height - env->map.width) *
																env->d.y) / 2;
}

int		keyhook(int key, void *data)
{
	t_env		*env;

	env = (t_env *)data;
	if (key == 0x35)
		exit(0);
	else if (ARROW_UP == key || key == ARROW_DOWN || key == NUMPAD_PLUS ||
			key == NUMPAD_MINUS || key == KEY_C || key == KEY_S)
	{
		if (key == ARROW_UP || key == ARROW_DOWN)
			rotate(env, key);
		else if (key == NUMPAD_PLUS || key == NUMPAD_MINUS)
		{
			env->dhmax += (key == NUMPAD_MINUS) ? 0.25 : -0.25;
			env->dh = env->dhmax * (fabs(env->rot) - env->d.x) / env->d.x;
		}
		if (key == ARROW_UP || key == ARROW_DOWN ||
			key == NUMPAD_PLUS || key == NUMPAD_MINUS)
			calc_map(*env);
		else if (key == KEY_C)
			env->colorstyle = (env->colorstyle == NONE) ? MAPCOLOR : NONE;
		else if (key == KEY_S)
			env->drawstyle = (env->drawstyle == WU) ? POINT : WU;
		update(*env);
	}
	return (0);
}
