/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 21:32:04 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/05 23:52:30 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#   include <stdio.h>
#include "minilibx_macos/mlx.h"
#include "fdf.h"

# define ARROW_UP 0x7e
# define ARROW_DOWN 0x7d
# define ARROW_LEFT 0x7b
# define ARROW_RIGHT 0x7c

int		keyhook(int key, void *data)
{
	t_env		*env;
	t_mlxdata	*mlxdata;
	int			*ptr;
	int			i;

	env = (t_env *)data;
	if (key == 0x35)
		exit(0);
	else if (ARROW_LEFT <= key && key <= ARROW_UP)
	{
		printf("key = %#x\n", key);
		if (key == ARROW_UP || key == ARROW_DOWN)
		{
			env->d.y = env->d.y + ((key == ARROW_UP) ? 5 : -5);
			env->d.y -= (fabs(env->d.y) > env->d.x) ? (int)env->d.y % (int)env->d.x : 0;
			mlxdata = getmlxdata(NULL);
			i = 0;
			ptr = (int *)(mlxdata->img);
			while (i < mlxdata->sizeline * WIN_H / 4)
				ptr[i++] = 0x00000000;
			mlx_put_image_to_window(mlxdata->mlx, mlxdata->win, mlxdata->imgptr, 0, 0);
			draw(*env);
			mlx_put_image_to_window(mlxdata->mlx, mlxdata->win, mlxdata->imgptr, 0, 0);
		}
	}
	return (0);
}
