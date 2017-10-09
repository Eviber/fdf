/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:47:48 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/09 22:10:33 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/libft.h"
#include "fdf.h"

int			**randmap(char *path, int *w, int *h)
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
			array[i][j] = rand() % 50;
	i = -1;
	while (++i < *h && (j = -1))
	{
		while (++j < *w)
			printf("%-5d", array[i][j]);
		printf("\n");
	}
	return (array);
}

#define BUFFER 1000000

char		*readfile(char *path)
{
	int		fd;
	int		i;
	int		nbuf;
	char	*str;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	nbuf = 1;
	str = malloc(BUFFER);
	while (i < BUFFER && read(fd, str + i, BUFFER - i))
	{
		
	}
	return (str);
}

int			**parsefile(char *path, int *w, int *h)
{
	char	*file;

	file = readfile(path);
}

t_map		parse(char *path)
{
	t_map	map;
	t_point	*ptr;
	int		i;

	if (ft_strequ(path, "-r"))
		map.array = randmap(path, &(map.width), &(map.height));
	else
		map.array = parsefile(path, &(map.width), &(map.height));
	map.grid = (t_point **)ft_memalloc(map.height * sizeof(t_point *) + (map.width * map.height * sizeof(t_point *)));
	ptr = (t_point *)(map.grid + map.height);
	i = -1;
	while (++i < map.height)
		map.grid[i] = ptr + (i * map.width);
	return (map);
}
