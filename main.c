/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 18:36:20 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/05 23:17:20 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include "minilibx_macos/mlx.h"
#include "libft.h"
#include "fdf.h"

t_mlxdata	*getmlxdata(char *name)
{
	static t_mlxdata	*data = NULL;

	if (data)
		return (data);
	data = (t_mlxdata *)malloc(sizeof(t_mlxdata));
	if (!data)
		return (NULL);
	if (!(data->mlx = mlx_init()))
		return (NULL);
	if (!(data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, name)))
		return (NULL);
	if (!(data->imgptr = mlx_new_image(data->mlx, WIN_W, WIN_H)))
		return (NULL);
	if (!(data->img = mlx_get_data_addr(data->imgptr, &(data->bpp),
										&(data->sizeline), &(data->endian))))
		return (NULL);
	data->bpp /= 8;
	return (data);
}

void		update(void)
{
	t_mlxdata	*data;
	int			*ptr;
	int			i;

	i = 0;
	data = getmlxdata(NULL);
	ptr = (int *)(data->img);
	mlx_put_image_to_window(data->mlx, data->win, data->imgptr, 0, 0);
	while (i < data->sizeline * WIN_H / 4)
		ptr[i++] = 0xFF000000;
}

void		draw(t_env	env)
{
	draw_grid(env);
	update();
	draw_map(env);
}

int			main(int argc, char **argv)
{
	t_mlxdata	*data;
	t_env		env;

	srand(time(NULL));
	if (argc != 2)
		return (-1);
	data = getmlxdata(argv[0]);
	env.map = parse(argv[1]);
	env.d.x = WIN_W / (env.map.width + env.map.height);
	env.d.y = env.d.x / 2;
	env.startpoint = env.d.y * (env.map.width + 1);
	mlx_hook(data->win, 2, 2, keyhook, &env);
	draw(env);
	mlx_put_image_to_window(data->mlx, data->win, data->imgptr, 0, 0);
	mlx_loop(data->mlx);
	return (0);
}
