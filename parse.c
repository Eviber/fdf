/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:47:48 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/05 15:17:36 by ygaude           ###   ########.fr       */
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
	*w = 10;//rand() % 101;
	*h = 10;//rand() % 101;
	array = (int **)ft_memalloc(*h * sizeof(int *) + (*w * *h * sizeof(int)));
	ptr = (int *)(array + *h);
	i = 0;
	while (i < *h)
	{
		array[i] = ptr + (i * *w);
		i++;
	}
	i = -1;
	while (++i < *h && (j = -1))
		while (++j < *w)
			array[i][j] = rand() % 10 * (fabs(i - 5) / 2.0) * (fabs(j - 9) / 2.0) - 10;
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

	map.array = readfile(path, &(map.width), &(map.height));
	return (map);
}
