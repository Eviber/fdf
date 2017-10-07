/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:47:48 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/07 13:44:13 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/libft.h"
#include "fdf.h"

int			**readfile(char *path, int *w, int *h)
{
	int		**array;
	int		*ptr;
	int		i;
	int		j;

	(void)path;
	*w = rand() % 50 + 2;
	*h = rand() % 50 + 2;
	array = (int **)ft_memalloc(*h * sizeof(int *) + (*w * *h * sizeof(int)));
	ptr = (int *)(array + *h);
	i = -1;
	while (++i < *h)
		array[i] = ptr + (i * *w);
	i = -1;
	while (++i < *h && (j = -1))
		while (++j < *w)
			array[i][j] = rand() % 20;
	i = -1;
	while (++i < *h && (j = -1))
	{
		while (++j < *w)
			printf("%-5d", array[i][j]);
		printf("\n");
	}
	return (array);
}

t_map		parse(char *path)
{
	t_map	map;
	t_point	*ptr;
	int		i;

	map.array = readfile(path, &(map.width), &(map.height));
	map.grid = (t_point **)ft_memalloc(map.height * sizeof(t_point *) + (map.width * map.height * sizeof(t_point *)));
	ptr = (t_point *)(map.grid + map.height);
	i = -1;
	while (++i < map.height)
		map.grid[i] = ptr + (i * map.width);
	return (map);
}
