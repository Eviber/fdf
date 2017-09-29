/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:47:48 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/29 23:16:59 by ygaude           ###   ########.fr       */
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

	(void)path;
	*w = 19;
	*h = 11;
	array = (int **)ft_memalloc(*h * sizeof(int *) + (*w * *h * sizeof(int)));
	ptr = (int *)(array + *h);
	i = 0;
	while (i < *h)
	{
		array[i] = ptr + i;
		i++;
	}
	return (array);
}

t_map		parse(char *path)
{
	t_map	map;

	map.array = readfile(path, &(map.width), &(map.height));
	return (map);
}
