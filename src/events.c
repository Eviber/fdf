/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 21:32:04 by ygaude            #+#    #+#             */
/*   Updated: 2017/12/10 16:53:46 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "libft.h"
#include "fdf.h"

void	update(t_env env)
{
	t_mlxdata	*mlxdata;
	int			*tmp;
	int			i;

	mlxdata = getmlxdata(NULL);
	tmp = (int *)mlxdata->img;
	i = 0;
	while (i < WIN_H * WIN_W)
		tmp[i++] = env.bg;
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

void	modifalti(t_env *env, int key)
{
	if (key == NUMPAD_PLUS || key == NUMPAD_MINUS)
		env->dhmax += (key == NUMPAD_MINUS) ? 0.01 : -0.01;
	else
		env->dhmax += (key == KEY_PGUP) ? 0.1 : -0.1;
	env->dh = env->dhmax * (fabs(env->rot) - env->d.x) / env->d.x;
}

void	toggle(t_env *env, int key)
{
	if (key == KEY_C)
		env->colorstyle = (env->colorstyle == NONE) ? MAPCOLOR : NONE;
	else if (key == KEY_S)
		env->drawstyle = (env->drawstyle == POINT) ? WU : POINT;
	else
		env->trnsvrsl = !env->trnsvrsl;
}

int		keyhook(int key, void *data)
{
	t_env		*env;

	env = (t_env *)data;
	if (key == 0x35)
		exit(0);
	if (key == ARROW_UP || key == ARROW_DOWN)
		rotate(env, key);
	else if (key == KEY_PGDWN || key == KEY_PGUP ||
			key == NUMPAD_PLUS || key == NUMPAD_MINUS)
		modifalti(env, key);
	if (key == ARROW_UP || key == ARROW_DOWN || key == KEY_PGDWN ||
		key == KEY_PGUP || key == NUMPAD_PLUS || key == NUMPAD_MINUS)
		calc_map(*env);
	else if (key == KEY_C || key == KEY_S || key == KEY_T)
		toggle(env, key);
	else if (key == 0xB)
		env->bg = ((unsigned)env->bg == 0xF0000000) ? 0 : 0xF0000000;
	update(*env);
	return (0);
}
