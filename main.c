/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 18:36:20 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/28 23:49:00 by ygaude           ###   ########.fr       */
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

void		draw(void)
{
}

#include <fcntl.h>
int			main(int argc, char **argv)
{
	t_mlxdata	*data;
	char		*line;
	int			*ptr;
	int			i;
	int			j;
	int			fd;

	if (argc != 2)
		return (-1);
	fd = open(argv[2], O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line) > 0)
		i++;
	data = getmlxdata(argv[0]);
	data->map = parse(argv[1], i);
	i = 0;
	while (data->map.grid[i])
	{
		j = 0;
		while (j < data->map.gridlen[i])
			printf("%d", data->map.grid[i][j++]);
		printf("\n");
		i++;
	}
	i = 0;
	ptr = (int *)(data->img);
	while (i < data->sizeline * WIN_H / 4)
		ptr[i++] = 0x00FFFFFF;
	mlx_put_image_to_window(data->mlx, data->win, data->imgptr, 0, 0);
	draw();
	mlx_put_image_to_window(data->mlx, data->win, data->imgptr, 0, 0);
	mlx_loop(data->mlx);
	return (0);
}
