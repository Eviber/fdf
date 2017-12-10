/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 18:36:20 by ygaude            #+#    #+#             */
/*   Updated: 2017/12/10 16:48:38 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "mlx.h"
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

void		draw(t_env env)
{
	draw_map(env);
}

t_env		initenv(char *str)
{
	t_env		env;

	env.map = parse(str);
	env.d.x = WIN_H / (env.map.width - 1 + env.map.height - 1);
	env.d.y = env.d.x / 2;
	env.rot = env.d.x / 2;
	env.dhmax = 10;
	env.dh = env.dhmax * (env.rot - env.d.x) / env.d.x;
	env.start = WIN_H / 2 - ((env.map.height - env.map.width) * env.d.y) / 2;
	env.drawstyle = WU;
	env.colorstyle = NONE;
	env.trnsvrsl = 0;
	env.bg = 0x00000000;
	return (env);
}

int			frame(void *env)
{
	if (env)
		update(*(t_env *)env);
	return (0);
}

int			main(int argc, char **argv)
{
	t_mlxdata	*data;
	t_env		env;

	if (argc != 2)
	{
		ft_putstr("usage: fdf -r | filename\n");
		return (0);
	}
	errno = 0;
	env = initenv(argv[1]);
	if (!(data = getmlxdata(argv[0])))
		exit_error("INIT ERROR\n");
	update(env);
	mlx_hook(data->win, 2, 2, keyhook, &env);
	mlx_loop_hook(data->mlx, frame, &env);
	calc_map(env);
	draw(env);
	mlx_put_image_to_window(data->mlx, data->win, data->imgptr, 0, 0);
	mlx_loop(data->mlx);
	return (0);
}
