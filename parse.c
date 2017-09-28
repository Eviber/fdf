/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:47:48 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/28 23:33:52 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/libft.h"
#include "fdf.h"

t_map		parse(char *path, int size)
{
	t_map	map;
	char	**splitstr;
	char	*line;
	int		fd;
	int		i;
	int		j;

	i = -1;
	fd = open(path, O_RDONLY);
	map.grid = (int **)malloc(sizeof(int *) * size + 1);
	map.gridlen = (int *)malloc(sizeof(int) * size);
	while (get_next_line(fd, &line) > 0)
	{
		splitstr = ft_strsplit(line, ' ');
		j = 0;
		while (splitstr[j])
			j++;
		map.grid[++i] = (int *)malloc(sizeof(int) * j);
		map.gridlen[i] = j;
		while (--j)
			map.grid[i][j] = ft_atoi(splitstr[j]);
	}
	map.grid[++i] = NULL;
	return (map);
}
