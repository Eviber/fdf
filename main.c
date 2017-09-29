/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 18:36:20 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/29 23:18:53 by ygaude           ###   ########.fr       */
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

void		draw(unsigned int c1, unsigned int c2)
{
	double	i;
	t_line	ln;

	i = 0;
	while (i < WIN_W)
	{
		ln.a.x = 0;
		ln.a.y = (i * WIN_H) / WIN_W;
		ln.b.x = WIN_W - i;
		ln.b.y = 0;
		drawline(ln.a, ln.b, c1, c2);
		update();
		ln.a.x = WIN_W;
		ln.a.y = (i * WIN_H) / WIN_W;
		ln.b.x = WIN_W - i;
		ln.b.y = WIN_H;
		drawline(ln.a, ln.b, c1, c2);
		update();
		i += WIN_W / 100;
	}
	while (i > 0)
	{
		ln.a.x = i;
		ln.a.y = 0;
		ln.b.x = WIN_W;
		ln.b.y = (i * WIN_H) / WIN_W;
		drawline(ln.a, ln.b, c1, c2);
		update();
		ln.a.x = i;
		ln.a.y = WIN_H;
		ln.b.x = 0;
		ln.b.y = (i * WIN_H) / WIN_W;
		drawline(ln.a, ln.b, c1, c2);
		update();
		i -= WIN_W / 100;
	}
}

int			main(int argc, char **argv)
{
	t_mlxdata	*data;

	srand(time(NULL));
	if (argc != 2)
		return (-1);
	parse("lol");
//	data = getmlxdata(argv[0]);
//	draw(0x00FF0000, 0x0000FF00);
//	mlx_loop(data->mlx);
	return (0);
}
