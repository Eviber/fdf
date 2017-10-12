/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 21:32:04 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/12 23:34:59 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#   include <stdio.h>
#include "minilibx_macos/mlx.h"
#include "libft.h"
#include "fdf.h"

# define ARROW_UP 0x7e
# define ARROW_DOWN 0x7d
# define ARROW_LEFT 0x7b
# define ARROW_RIGHT 0x7c

void	rotate(t_env *env, int key)
{
	env->rot += 5 * (env->d.x / 100) * ((key == ARROW_UP) ? -1 : 1);
	if (env->rot > env->d.x * 2 || env->rot < -env->d.x * 2)
		env->rot = (env->rot > 0) ? -env->d.x * 2 : env->d.x * 2;
	env->dh = 1 * (fabs(env->rot) - env->d.x) / env->d.x;
	env->d.y = env->rot;
	if (env->rot < -env->d.x)
		env->d.y = env->rot - 2 * (env->rot + env->d.x);
	else if (env->rot > env->d.x)
		env->d.y = env->rot - 2 * (env->rot - env->d.x);
	env->startpoint = WIN_H / 2  - ((env->map.height - env->map.width) * env->d.y) / 2;
}

int		keyhook(int key, void *data)
{
	t_env		*env;
	t_mlxdata	*mlxdata;

	env = (t_env *)data;
//	printf("key = %#x\n", key);
	if (key == 0x35)
		exit(0);
	else if (ARROW_LEFT <= key && key <= ARROW_UP)
	{
		if (key == ARROW_UP || key == ARROW_DOWN)
		{
			mlxdata = getmlxdata(NULL);
			rotate(env, key);
			ft_memset(mlxdata->img, 0, mlxdata->sizeline * WIN_H);
			mlx_put_image_to_window(mlxdata->mlx, mlxdata->win, mlxdata->imgptr, 0, 0);
			draw(*env);
			mlx_put_image_to_window(mlxdata->mlx, mlxdata->win, mlxdata->imgptr, 0, 0);
		}
	}
	return (0);
}
