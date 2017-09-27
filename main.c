/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 18:36:20 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/27 22:52:15 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_line
{
	t_point		a;
	t_point		b;
}				t_line;

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

void		imgputpixel(t_mlxdata dt, t_point pos, unsigned int color)
{
	unsigned int	*addr;

	addr = (unsigned int *)(dt.img + (dt.sizeline * pos.y) + (pos.x * dt.bpp));
	if (pos.x < 640 && pos.y < 480)
		*addr = color;
}

void		drawline(t_mlxdata data, t_line ln, unsigned int color)
{
	t_point	d;
	t_point	s;
	int		err;
	int		tmp;

	d.x = (ln.a.x > ln.b.x) ? ln.a.x - ln.b.x : ln.b.x - ln.a.x;
	d.y = (ln.a.y > ln.b.y) ? ln.a.y - ln.b.y : ln.b.y - ln.a.y;
	s.x = (ln.a.x < ln.b.x) ? 1 : -1;
	s.y = (ln.a.y < ln.b.y) ? 1 : -1;
	err = (d.x > d.y ? d.x : -(d.y))/2;
	while (!(ln.a.x == ln.b.x && ln.a.y == ln.b.y))
	{
		imgputpixel(data, ln.a, color);
		tmp = err;
		err -= (tmp > -d.x) ? d.y : 0;
		err += (tmp < d.y) ? d.x : 0;
		ln.a.x += (tmp > -d.x) ? s.x : 0;
		ln.a.y += (tmp < d.y) ? s.y : 0;
	}
	imgputpixel(data, ln.a, color);
}

void		draw(t_mlxdata data)
{
	t_line	line;

	line.a.x = 0;
	line.a.y = 0;
	line.b.x = 640;
	line.b.y = 0;
	drawline(data, line, 0x00CCCCFF);
	while (line.a.y < 480)
	{
		line.b.y = line.a.y;
		drawfatline(10, data, line, 0x00CCCCFF);
		drawline(data, line, 0x00FF0000);
		line.a.y += 20;
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
	mlx_put_image_to_window(data.mlx, data.win, data.imgptr, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
