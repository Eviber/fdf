/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 18:36:20 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/26 00:07:45 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct	s_mlxdata
{
	void			*mlx;
	void			*win;
	void			*imgptr;
	char			*img;
	int				bpp;
	int				sizeline;
	int				endian;
}				t_mlxdata;

void		imgputpixel(t_mlxdata dt, t_pos pos, unsigned int color)
{
	unsigned int	*addr;

	addr = (unsigned int *)(dt.img + (dt.sizeline * pos.x) + (pos.y * dt.bpp));
	*addr = color;
}

void		draw(t_mlxdata data)
{
	t_pos	pos;

	pos.x = 0;
	pos.y = 0;
	while (pos.x < 480)
	{
		pos.y = 0;
		while (pos.y < 640)
		{
			imgputpixel(data, pos, 0x00ffffff);
			pos.y += 20;
		}
		pos.x += 20;
	}
}

int			main(int argc, char **argv)
{
	t_mlxdata	data;

	if (!(data.mlx = mlx_init()))
		return (-1);
	if (!(data.win = mlx_new_window(data.mlx, 640, 480, argv[0])))
		return (-1);
	if (!(data.imgptr = mlx_new_image(data.mlx, 640, 480)))
		return (-1);
	data.img = mlx_get_data_addr(data.imgptr, &(data.bpp), &(data.sizeline), &(data.endian));
	data.bpp /= 8;
	draw(data);
	mlx_put_image_to_window(data.mlx, data.win, data.imgptr, -15, -15);
	mlx_loop(data.mlx);
	return (0);
}
