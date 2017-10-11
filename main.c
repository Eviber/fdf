/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 18:36:20 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/11 16:03:36 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
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
//	draw_grid(env);
	draw_map(env);
}

char		*readfile(char *path);

int			main(int argc, char **argv)
{
	t_mlxdata	*data;
	t_env		env;
	char		*str;

	errno = 0;
	parse(argv[1]);
	return (0);
	srand(time(NULL));
	if (argc != 2)
		return (-1);
	data = getmlxdata(argv[0]);
	env.map = parse(argv[1]);
	env.d.x = WIN_H / (env.map.width + env.map.height);
	env.d.y = env.d.x;
	env.dh = 0;
	env.rot = env.d.x;
	env.startpoint = env.map.width * env.d.y;
	mlx_hook(data->win, 2, 2, keyhook, &env);
	draw(env);
	mlx_put_image_to_window(data->mlx, data->win, data->imgptr, 0, 0);
	mlx_loop(data->mlx);
	return (0);
}
